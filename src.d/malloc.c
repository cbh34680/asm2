#include <stds.h>
//
// K&R malloc
// https://ofstack.com/C++/8457/implementation-code-and-analysis-based-on-malloc-and-free-function.html
//

typedef long Align;

union header
{
	struct
	{
		union header *ptr;
		size_t size;
	}s;

	Align x;
};

typedef union header Header;

static Header base;
static Header *freep = NULL;

static Header *morecore(size_t nu);

void *malloc(size_t nbytes)
{
	Header *p, *prevp;
	size_t nunits;

	nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
	prevp = freep;

	if(prevp == NULL)
	{
		base.s.ptr = freep = prevp = &base;
		base.s.size = 0;
	}

	for (p=prevp->s.ptr; ;prevp=p, p=p->s.ptr)
	{
		if(p->s.size >= nunits)
		{
			if (p->s.size == nunits)
			{
				// freep リストから外す

				prevp->s.ptr = p->s.ptr;
			}
			else
			{
				// ブロックの後方を削る

				p->s.size -= nunits;

				p += p->s.size;
				p->s.size = nunits;
			}

			// アロケートブロック検出用に追加
			p->s.ptr = NULL;

			// freep はリンクの一つ前に設定
			freep = prevp;

			return (void*)(p + 1);
		}

		if (p == freep)
		{
			// brk を広げて、その領域を freep につなげる

			p = morecore(nunits);

			if (p == NULL)
			{
				return NULL;
			}
		}
	}
}

//#define NALLOC 1024
#define NALLOC 6

static Header *morecore(size_t nu)
{
	if(nu < NALLOC)
	{
		nu = NALLOC;
	}

	char * const cp = sbrk(nu * sizeof(Header));
	if(cp == (char *)-1)
	{
		return NULL;
	}

	Header * const up = (Header *)cp;

	up->s.size = nu;

	free((void *)(up + 1));

	return freep;
}

void free(void *ap)
{
	// nop if free(NULL)
	if (! ap)
		return;

	Header * const pa = (Header *)ap - 1;
	Header *pf = freep;

	for (; ; pf=pf->s.ptr)
	{
		// free --> [pa] <-- free			... free ブロックに挟まれた領域かチェック
		// [pf]              [pf->s.ptr]

		if (pf < pa && pa < pf->s.ptr)
			break;

		//

		if(pf->s.ptr <= pf && (pf < pa || pa < pf->s.ptr))
			break;
	}

	if ((pa + pa->s.size) == pf->s.ptr)
	{
		pa->s.size += pf->s.ptr->s.size;
		pa->s.ptr   = pf->s.ptr->s.ptr;
	}
	else
	{
		pa->s.ptr = pf->s.ptr;
	}

	if ((pf + pf->s.size) == pa)
	{
		pf->s.size += pa->s.size;
		pf->s.ptr   = pa->s.ptr;
	}
	else
	{
		pf->s.ptr = pa;
	}

	freep = pf;
}

void *realloc(void *ptr, size_t size)
{
	if (ptr)
	{
		if (size == 0)
		{
			// size が 0 で ptr が NULL でない場合には、 free(ptr) と等価である

			free(ptr);
			return NULL;
		}
	}
	else
	{
		//  ptr が NULL の場合には malloc(size) と等価である

		return malloc(size);
	}

	Header *bp = (Header *)ptr - 1;

	if (size == bp->s.size)
	{
		return ptr;
	}
	else if (size < bp->s.size)
	{
		// 領域の先頭から、新旧のサイズの小さい方の位置までの範囲の内容は 変更されない。

		// !! malloc と同様の分割を実装
		return ptr;
	}

	// np: 一つ先のブロック
	Header *np = bp + bp->s.size;

	


	return NULL;
}

void const *uc_get_base(int target)
{
	if (target == 0)
		return &base;

	return base.s.ptr;
}

void const *uc_get_freep(void)
{
	return freep;
}

void const *uc_walk_freep(uc_walk_callback cb_free)
{
	// check allocated
	if (! freep)
		return NULL;

	// empty freep
	if (freep->s.ptr == &base)
		return NULL;

	// freep --> base --> f1 --> f2
	//            ^              |
	//            |              |
	//            b4 <--- f3 <---+

	for (Header const *pf=freep; ; pf=pf->s.ptr)
	{
		//if (pf != &base)
		if (pf->s.size)
		{
			void const *addr = pf;
			void const *next = pf->s.ptr;

			_Bool endloop = cb_free(addr, pf->s.size * sizeof(Header), pf==freep, next);
			if (endloop)
				return addr;
		}

		if (pf->s.ptr == freep)
		{
			break;
		}
	}

	return NULL;
}

void const *uc_walk_heap(uc_walk_callback cb_free, uc_walk_callback cb_alloc)
{
	if (! freep)
	{
		// no allocated once
		return NULL;
	}

	// .data の最後をページ単位にアライメント
	void const * const phs = (void *)PAGE_ALIGNED(&end);

	// 現在の brk
	void const * const phe = sbrk(0);

	// ヒープ領域全体を走査
	for (Header const *pb=(Header *)phs; (void*)pb<phe; pb+=pb->s.size)
	{
#if 1
		// check base
		if (! pb->s.size)
			continue;

		if (pb->s.ptr)
		{
			// 次のブロックへのリンクがある --> 空き領域

			if (cb_free)
			{
				void const *addr = pb;
				void const *next = pb->s.ptr;

				_Bool endloop = cb_free(addr, pb->s.size * sizeof(Header), pb==freep, next);
				if (endloop)
					return addr;
			}
		}
		else
		{
			// 利用中の領域

			if (cb_alloc)
			{
				void const *addr = pb;
				void const *next = pb->s.ptr;

				_Bool endloop = cb_alloc(addr, pb->s.size * sizeof(Header), 0, next);

				if (endloop)
					return addr;
			}
		}

#else
		// freep を走査
		for (Header const *pf=freep; ; pf=pf->s.ptr)
		{
			if (pb == pf)
			{
				// freep リスト中に登録がある --> 空き領域

				if (cb_free)
				{
					void const *addr = pb;
					void const *next = pb->s.ptr;

					_Bool endloop = cb_free(addr, (pb->s.size - 1) * sizeof(Header), pb==freep, next);
					if (endloop)
						return addr;
				}

				goto NEXT_LOOP;
			}

			if (pf->s.ptr == freep)
			{
				// 利用中の領域

				if (cb_alloc)
				{
					void const *addr = pb;
					void const *next = pb->s.ptr;

					_Bool endloop = cb_alloc(addr, (pb->s.size - 1) * sizeof(Header), 0, next);

					if (endloop)
						return addr;
				}

				goto NEXT_LOOP;
			}
		}

		assert(0);

NEXT_LOOP:
		;
#endif
	}

	return NULL;
}

// EOF

