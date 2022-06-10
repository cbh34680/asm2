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
	char *cp;
	Header *up;

	if(nu < NALLOC)
	{
		nu = NALLOC;
	}

	cp = sbrk(nu * sizeof(Header));
	if(cp == (char *)-1)
	{
		return NULL;
	}

	up = (Header *)cp;
	up->s.size = nu;

	free((void *)(up + 1));

	return freep;
}

void free(void *ap)
{
	if (! ap)
	{
		return;
	}

	Header *bp,*p;
	bp = (Header *)ap - 1;

	for (p=freep; !(bp > p && bp < p->s.ptr); p=p->s.ptr)
	{
		if(p >= p->s.ptr && (bp>p || bp<p->s.ptr))
		{
			break;
		}
	}

	if (bp+bp->s.size == p->s.ptr)
	{
		// 後のブロックと結合

		bp->s.size += p->s.ptr->s.size;
		bp->s.ptr = p->s.ptr->s.ptr;
	}
	else
	{
		// 後ろのリンクと接続

		bp->s.ptr = p->s.ptr;
	}

	if (p+p->s.size == bp)
	{
		// 前のブロックと結合

		p->s.size += bp->s.size;
		p->s.ptr = bp->s.ptr;
	}
	else
	{
		// 前のリンクと接続

		p->s.ptr = bp;
	}

	// freep はリンクの一つ前に設定

	freep = p;
}

void const *uc_get_base()
{
	return &base;
}

void const *uc_get_freep()
{
	return freep;
}

void const *uc_walk_freep(uc_walk_callback cb_free)
{
	if (! freep)
	{
		// no allocated once
		return NULL;
	}

	if (freep->s.ptr != &base)
	{
		for (Header const *pf=freep; ; pf=pf->s.ptr)
		{
			if (pf != &base)
			{
				void const *addr = pf + 1;
				void const *next = pf->s.ptr;

				_Bool endloop = cb_free(addr, (pf->s.size - 1) * sizeof(Header), pf==freep, next);
				if (endloop)
					return addr;
			}

			if (pf->s.ptr == freep)
			{
				break;
			}
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
		// freep を走査
		for (Header const *pf=freep; ; pf=pf->s.ptr)
		{
			if (pb == pf)
			{
				// freep リスト中に登録がある --> 空き領域

				if (cb_free)
				{
					void const *addr = pb + 1;
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
					void const *addr = pb + 1;
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
	}

	return NULL;
}

// EOF

