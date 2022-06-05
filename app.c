#include <stds.h>

char buf[1024];

static void test1()
{
	char haystack[] = "Abfhi\0aBc";

	const void* mem1 = memchr(haystack, 'f', 9);
	const void* mem2 = memchr(haystack, 'B', 9);
	const void* mem3 = memchr(haystack, 'i', 9);

	puts(mem1 ? mem1 : "NULL");
	puts(mem2 ? mem2 : "NULL");
	puts(mem3 ? mem3 : "NULL");

	const char* pos1 = strchr(haystack, 'b');
	const char* pos2 = strchr(haystack, 'B');

	puts(pos1 ? pos1 : "NULL");
	puts(pos2 ? pos2 : "NULL");

	const void* s1 = ua_getsp();
	char* d1 = alloca(16);
	const void* s2 = ua_getsp();

	assert(s2 == d1);
	assert((s1 - s2) == 16);

	puts(ua_pgx(buf, (unsigned long)s1));
	puts(ua_pgx(buf, (unsigned long)d1));
	puts(ua_pgx(buf, (unsigned long)s2));

	puts(memset(buf, '@', 15));
	buf[15]= '\0';

	puts("123456789012345678901234567890");
	puts(buf);

	// https://qiita.com/EqualL2/items/168e083caa5f07a1105b

	int x = log10(255) + 1;
}

static void test2()
{
	const char* s = "ABCDE";

	char sz[100] = { 0 };

	puts(memset(sz, '-', sizeof(sz) - 1));

	puts(strcpy(sz, "abcde"));
	puts(memmove(sz + 2, sz, 2));

	memset(sz, '-', sizeof sz);
	puts(memmove(sz, s, strlen(s) + 1));

	memset(sz, '-', sizeof sz);
	puts(memcpy(sz, s, strlen(s) + 1));

	memset(sz, '-', sizeof sz);
	puts(strcpy(sz, s));
}

static void test3()
{
	const int fd = open("/home/user/asm/a.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);

	close(fd);
}

static void test4()
{
	puts("   1234567890123456789");
	puts("   0123456789012345678");

	strcpy(buf, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	uc_prints("0x[");
	uc_prints(ua_pgx(buf, -2));
	puts("]");

	strcpy(buf, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	uc_prints("0x[");
	uc_prints(ua_pwx(buf, 2));
	puts("]");

	strcpy(buf, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	uc_prints("0x[");
	uc_prints(ua_phx(buf, 5));
	puts("]");
}

static void test5()
{
	int x = atoi("111a");
	puts(ua_pwx(buf, x));

/*
	puts("==========");

	for (int i=0; i<8192; i++)
	{
		uc_prints(ua_phx(buf, i));
		uc_prints("=");
		puts(ua_phx(buf, PAGE_ALIGNED(i)));
	}

	puts("==========");
*/
}

static void test6()
{
	puts(ua_phx(buf, memcmp("032", "022", 4)));
	puts(ua_phx(buf, memcmp("022", "022", 4)));
	puts(ua_phx(buf, memcmp("012", "022", 4)));

	puts(ua_phx(buf, strcmp("032", "022")));
	puts(ua_phx(buf, strcmp("022", "022")));
	puts(ua_phx(buf, strcmp("012", "022")));


}

int global_data1 = 100;
int global_data2 = 200;

int global_bss1;
int global_bss2;

static void test7()
{
	uc_prints("test7=");
	puts(ua_pgx(buf, (unsigned long)test7));
	uc_prints("etext=");
	puts(ua_pgx(buf, (unsigned long)&etext));
	uc_prints("global_data1=");
	puts(ua_pgx(buf, (unsigned long)&global_data1));
	uc_prints("global_data2=");
	puts(ua_pgx(buf, (unsigned long)&global_data2));
	uc_prints("edata=");
	puts(ua_pgx(buf, (unsigned long)&edata));
	uc_prints("__bss_start=");
	puts(ua_pgx(buf, (unsigned long)&__bss_start));
	uc_prints("global_bss1=");
	puts(ua_pgx(buf, (unsigned long)&global_bss1));
	uc_prints("global_bss2=");
	puts(ua_pgx(buf, (unsigned long)&global_bss2));
	uc_prints("end=");
	puts(ua_pgx(buf, (unsigned long)&end));
}

static void prt_(const char *name, const void *pos)
{
	uc_prints("[");
	uc_prints(name);
	uc_prints("]\t");

		uc_prints("\t");
		uc_prints(ua_pgx(buf, (unsigned long)pos));

		puts("");
}

#define prt(v) prt_(#v, (v))

static void cb_freep(const void *mem, size_t siz)
{
	uc_prints("\tfreep: ");
	uc_prints(ua_pgx(buf, (unsigned long)mem));
	uc_prints(", ");
	puts(ua_pgx(buf, siz));
}

static void cb_alloc(const void *mem, size_t siz)
{
	uc_prints("\talloc: ");
	uc_prints(ua_pgx(buf, (unsigned long)mem));
	uc_prints(", ");
	puts(ua_pgx(buf, siz));
}

void uc_walk_freep(
	void(* cb_freep)(const void *, size_t),
	void(* cb_alloc)(const void *, size_t)
);

void const *uc_get_base();
void const *uc_get_freep();

static void test8()
{
	puts("@@ init @@");
	void *left = sbrk(0);
	prt(left);

	void const *base = uc_get_base();
	prt(base);

	void const *freep = uc_get_freep();

//
	void *p1 = NULL;
	void *p2 = NULL;
	void *p3 = NULL;
	void *p4 = NULL;

	puts("-------------------------------------");
	puts("@@ alloc @@");

	p1 = malloc(16);
	prt(p1);
	p2 = malloc(16);
	prt(p2);
	p3 = malloc(16);
	prt(p3);
	p4 = strdup("abcde");
	prt(p4);

	puts("-------------------------------------");
	puts("@@ walk @@");

	uc_walk_freep(cb_freep, cb_alloc);

	puts("-------------------------------------");
	puts("@@ free @@");

	free(p2);
	prt(p2);
	free(p4);
	prt(p4);
	free(p1);
	prt(p1);
	free(p3);
	prt(p3);

	puts("-------------------------------------");
	puts("@@ walk @@");

	uc_walk_freep(cb_freep, cb_alloc);

//
	puts("-------------------------------------");
	puts("@@ last @@");

	void *right = sbrk(0);
	prt(right);

	freep = uc_get_freep();
	prt(freep);
}

static void test9()
{
	void *curr = NULL;
	void *prev = NULL;

	for (int i=0; i<20; i++)
	{
		curr = sbrk(0);

		if (curr == prev)
		{
			uc_prints("                       ");
		}
		else
		{
			uc_prints("before=");
			uc_prints(ua_pgx(buf, (unsigned long)curr));
		}

		void *p = malloc(4000);

		uc_prints(" after=");
		puts(ua_pgx(buf, (unsigned long)p));

		prev = curr;
	}
}

static void test10(long a, long b, long c)
{
	const void* s1 = ua_getsp();
	const void* d1 = strdupa("HEllO wOrlD");
	const void* s2 = ua_getsp();

	puts(ua_pgx(buf, (unsigned long)s1));
	puts(ua_pgx(buf, (unsigned long)d1));
	puts(ua_pgx(buf, (unsigned long)s2));

	puts(d1);

	assert((s1 - s2) == 16);
	assert(d1 == s2);
}

static void test11()
{
	void *bp = NULL, *bp_first = NULL;
	void *caller = (void *)-1;

	for (int i=0; i<9999 && caller; i++)
	{
		caller = ua_bt_caller(i, &bp);

		if (! bp_first)
		{
			bp_first = bp;
		}

		uc_prints(ua_pgx(buf, (unsigned long)caller));
		uc_prints("\t");
		puts(ua_pgx(buf, (unsigned long)bp));
	}

	puts(ua_pgx(buf, (unsigned long)(bp - bp_first)));
}

// https://qiita.com/nori26/items/9ccef61571602a6a3b45

typedef struct
{
	unsigned int	gp_offset;			//汎用レジスタ分のオフセット
	unsigned int	fp_offset;			//浮動小数点レジスタ分のオフセット
	void			*overflow_arg_area;	//スタック渡し分のアドレス
	void			*reg_save_area;		//レジスタ渡し分の先頭アドレス

	void			*_fp_save_area;
	void			*_end_reg_save_area;
	void			*_end_fp_save_area;
}
va_list[1];

void va_start_(va_list ap, void *last)
{
	void *bp;

	ua_bt_caller(1, &bp);

	ap->gp_offset = 0UL;
	ap->fp_offset = 0UL;

	ap->overflow_arg_area	= bp + 0x10;
	ap->reg_save_area		= bp - 0xa8;
	ap->_fp_save_area		= bp - 0x80;

	// rsi, rdx, rcx, r8, r9
	ap->_end_reg_save_area	= ap->reg_save_area + ( sizeof(void *) * 5 );

	// xmm0 - 7
	ap->_end_fp_save_area	= ap->_fp_save_area + ( sizeof(__int128_t) * 8 );
}

void va_end(va_list ap)
{
	ap->gp_offset = 0UL;
	ap->fp_offset = 0UL;

	ap->overflow_arg_area	= NULL;
	ap->reg_save_area		= NULL;

	ap->_fp_save_area		= NULL;

	ap->_end_reg_save_area	= NULL;
	ap->_end_fp_save_area	= NULL;
}

#define va_start(ap, last) va_start_((ap), &last)

double va_arg_f(va_list ap)
{
	return 1;
}

unsigned long va_arg(va_list ap)
{
	return 3;
}

#define va_arg(ap, type) (type)_Generic( \
  ((type) 0), double:va_arg_f, float:va_arg_f, default:va_arg)( (ap) )

static unsigned char foo(const char *format, ...)
{
	void *bp;
	unsigned char al;

	//ua_bt_caller(0, &bp);

	//__asm__ volatile("mov %0, %%al" : "=r"(al));
	__asm__ volatile
	(
		"mov %[val1], %%rbp\n\t"
		"mov %[val2], %%al\n\t"
			:
		[val1]"=r"(bp),
		[val2]"=r"(al)
	);

	puts("[reg]");
	unsigned long *ul_a = (unsigned long *)(bp - 0xa8);
	for (int i=0; i<5; i++)
	{
		unsigned long *ul = (unsigned long *)&ul_a[i];
		puts(ua_pgx(buf, *ul));
	}

	puts("[xmm]");
	puts(ua_pbx(buf, al));
	__uint128_t *ui128_a = (__uint128_t *)(bp - 0x80);
	for (int i=0; i<al; i++)
	{
		//double *dp = (double *)&ui128_a[i];
		unsigned long *dp = (unsigned long *)&ui128_a[i];
		puts(ua_pgx(buf, *dp));
	}

	puts("[stack]");
	ul_a = (unsigned long *)(bp + 0x10);
	for (int i=0; i<4; i++)
	{
		unsigned long *ul = (unsigned long *)&ul_a[i];
		puts(ua_pgx(buf, *ul));
	}

	puts("[va]");

	va_list args;
	va_start(args, format);

	puts(ua_pgx(buf, va_arg(args, int)));
	puts(ua_pgx(buf, va_arg(args, float)));
	puts(ua_pgx(buf, va_arg(args, double)));

	va_end(args);

	return al;
}

static void test12()
{
	char c = 0x1;
	short s = 0x2;
	int i = 0x3;
	long l = 0x4;
	char* p = (char*)0x5;
	double d = 0x6;

	puts(ua_pbx(buf, foo("", c, c, c, c, 0xff, d, d, d, d, d, d, d, d, i, s, l, p)));

	//foo("", d);
	//foo("", d, d, d);
	//foo("", d, d, d, d, d, d, d, d, d, d);
	//puts(ua_pbx(buf, foo("", c, s, i, l, p, c, s, i, l, p)));
	//puts(ua_pbx(buf, foo("", c, s, i, d, p, c, s, i, d, p)));
	//puts(ua_pbx(buf, foo("", d)));
	//puts(ua_pbx(buf, foo("", d)));

	//foo("aaa", "bbb", "ccc", "ddd", "eee", "fff", "000", "111", "222", "333", "444", "555");

}

int main(int argc, char** argv, char** envs)
{
	char s[1024];

	ua_test();

	for (int i=0; i<argc; i++) {
		uc_prints("argv=");
		puts(argv[i]);
	}

	puts("|--- 1");
	test1();
	puts("|--- 2");
	test2();
	puts("|--- 3");
	test3();
	puts("|--- 4");
	test4();
	puts("|--- 5");
	test5();
	puts("|--- 6");
	test6();
	puts("|--- 7");
	test7();
	puts("|--- 8");
	test8();
	puts("|--- 9");
	test9();
	puts("|--- 10");
	test10(1, 2, 3);
	puts("|--- 11");
	test11();
	puts("|--- 12");
	test12();

	return 2;
}

// EOF
