#include <stds.h>

//
// backtrace
// "-fno-omit-frame-pointer" のオプションが必要
//
#define USE_BT

char gbuf[1024];

static void test01()
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

	puts(memset(gbuf, ',', 15));
	gbuf[15]= '\0';

	puts("123456789012345678901234567890");
	puts(gbuf);

	// https://qiita.com/EqualL2/items/168e083caa5f07a1105b

	int n = 255;
	int x = log10(n) + 1;
	printf("log10(%d)+1 = %d\n", n, x);
}

static void test02()
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

static void test03()
{
	const int fd = open("/home/user/asm/a.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);

	close(fd);
}

static void test04()
{
	puts("   1234567890123456789");
	puts("   0123456789012345678");

	strcpy(gbuf, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	printf("0x[%lx]\n", -2);

	strcpy(gbuf, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	printf("0x[%x]\n", 12312312);

	strcpy(gbuf, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	printf("0x[%s]\n", ua_phx(gbuf, 143));
}

static void test05()
{
	int x = atoi("111a");
	printf("%d\n", x);

/*
	puts("==========");

	for (int i=0; i<8192; i++)
	{
		uc_prints(ua_phx(gbuf, i));
		uc_prints("=");
		puts(ua_phx(gbuf, PAGE_ALIGNED(i)));
	}

	puts("==========");
*/
}

static void test06()
{
	printf("%d\n", memcmp("032", "022", 4));
	printf("%d\n", memcmp("022", "022", 4));
	printf("%d\n", memcmp("012", "022", 4));

	printf("%d\n", strcmp("032", "022"));
	printf("%d\n", strcmp("022", "022"));
	printf("%d\n", strcmp("012", "022"));
}

int global_data1 = 100;
int global_data2 = 200;

int global_bss1;
int global_bss2;

static void test07()
{
	printf("test07=%lx\n", test07);
	printf("etext=%lx\n", &etext);
	printf("global_data1=%lx\n", &global_data1);
	printf("global_data2=%lx\n", &global_data2);
	printf("edata=%lx\n", &edata);
	printf("__bss_start=%lx\n", &__bss_start);
	printf("global_bss1=%lx\n", &global_bss1);
	printf("global_bss2=%lx\n", &global_bss2);
	printf("end=%lx\n", &end);
}

#define CB_TO_DATA(a)  ( (void *)(a) + 16 )

static _Bool cb_free(const void *addr, size_t size, _Bool isfreep, const void *next)
{
	const char *s = (char *)CB_TO_DATA(addr);

	printf("\tfree:\taddr=%p, size=%lu, isfreep=%d, next=%p, data=[%c%c]\n",
		addr, size, isfreep, next, s[0], s[1]);

	//if (s[1] == '2') return 1;

	return 0;
}

static _Bool cb_alloc(const void *addr, size_t size, _Bool isfreep, const void *next)
{
	const char *s = (char *)CB_TO_DATA(addr);

	printf("\talloc:\taddr=%p, size=%lu, isfreep=%d, next=%p, data=[%c%c]\n",
		addr, size, isfreep, next, s[0], s[1]);

	return 0;
}

static void prt_(char const *name, void const *pos)
{
	printf("[%s]\t\t%p\n", name, pos);
}

#define prt(v) prt_(#v, (v))

static void test08()
{
	puts("@@ init @@");
	void *left = sbrk(0);
	prt(left);

	void const * const base = uc_get_base(0);
	void const *bnext = NULL;

	prt(base);

	bnext = uc_get_base(1);
	prt(bnext);

	void const *freep = uc_get_freep();

//
	void *p1 = NULL;
	void *p2 = NULL;
	void *p3 = NULL;
	void *p4 = NULL;
	void *p5 = NULL;
	void *p6 = NULL;
	void const *wlast = NULL;

	puts("-------------------------------------");
	puts("@@ alloc @@");

	p1 = malloc(16);
	strcpy(p1, "p1");
	prt(p1);

	p2 = malloc(16);
	strcpy(p2, "p2");
	prt(p2);

	p3 = malloc(16);
	strcpy(p3, "p3");
	prt(p3);

	p4 = strdup("p4");
	prt(p4);

	p5 = strdup("p5");
	prt(p5);

	p6 = strdup("p6");
	prt(p6);

	puts("-------------------------------------");
	puts("@@ some free @@");

	free(p2);
	prt(p2);
	p2 = NULL;

	free(p5);
	prt(p5);
	p5 = NULL;

	puts("-------------------------------------");
	puts("@@ heap walk @@");

	freep = uc_get_freep();
	prt(freep);
	bnext = uc_get_base(1);
	prt(bnext);

	wlast = uc_walk_heap(cb_free, cb_alloc);
	prt(wlast);

	puts("-------------------------------------");
	puts("@@ freep walk @@");

	freep = uc_get_freep();
	prt(freep);
	bnext = uc_get_base(1);
	prt(bnext);

	uc_walk_freep(cb_free);

	puts("-------------------------------------");
	puts("@@ cleanup @@");

	free(p1);
	prt(p1);
	free(p2);
	prt(p2);
	free(p3);
	prt(p3);
	free(p4);
	prt(p4);
	free(p5);
	prt(p5);
	free(p6);
	prt(p6);

	puts("-------------------------------------");
	puts("@@ heap walk @@");

	uc_walk_heap(cb_free, cb_alloc);

	puts("-------------------------------------");
	puts("@@ freep walk @@");

	uc_walk_freep(cb_free);

//
	puts("-------------------------------------");
	puts("@@ last @@");

	void *right = sbrk(0);
	prt(right);

	freep = uc_get_freep();
	prt(freep);
}

static void test09()
{
	void *curr = NULL;
	void *prev = NULL;

	void *arr[10];

	for (int i=0; i<(sizeof(arr) / sizeof(arr[0])); i++, prev=curr)
	{
		curr = sbrk(0);

		if (curr == prev)
		{
			printf("                       ");
		}
		else
		{
			printf("before=%lx\n", curr);
		}

		void *p = malloc(4000);
		printf(" after=%lx\n", p);

		arr[i] = p;
	}

	uc_walk_heap(cb_free, cb_alloc);

	puts("*");

	for (int i=0; i<(sizeof(arr) / sizeof(arr[0])); i++)
	{
		free(arr[i]);
	}

	uc_walk_heap(cb_free, cb_alloc);

	puts("*");
}

static void test10(long a, long b, long c)
{
	const void* s1 = ua_getsp();
	const void* d1 = strdupa("HEllO wOrlD");
	const void* s2 = ua_getsp();

	printf("s1=0x%lx\nd1=0x%lx '%s'\ns2=0x%lx\n", s1, d1, d1, s2);

	puts(d1);

	assert((s1 - s2) == 16);
	assert(d1 == s2);

	ua_setsp(s1);
	printf("last=%p\n", ua_getsp());
}

static void test11()
{
	void *bp = NULL, *bp_first = NULL;
	void *caller = (void *)-1;

	for (int i=0; i<99 && caller; i++)
	{
		caller = ua_bt_caller(i, &bp);

		if (! bp_first)
		{
			bp_first = bp;
		}

		printf("%lx\t%lx\n", caller, bp);
	}

	printf("0x%lx (%d)\n", bp - bp_first, bp - bp_first);
}

#if 0
static unsigned char va_test_raw(const char *_nouse, ...)
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
		puts(ua_pgx(gbuf, *ul));
	}

	puts("[xmm]");
	puts(ua_pbx(gbuf, al));
	__uint128_t *ui128_a = (__uint128_t *)(bp - 0x80);
	for (int i=0; i<al; i++)
	{
		//double *dp = (double *)&ui128_a[i];
		unsigned long *dp = (unsigned long *)&ui128_a[i];
		puts(ua_pgx(gbuf, *dp));
	}

	puts("[stack]");
	ul_a = (unsigned long *)(bp + 0x10);
	for (int i=0; i<4; i++)
	{
		unsigned long *ul = (unsigned long *)&ul_a[i];
		puts(ua_pgx(gbuf, *ul));
	}

	return al;
}
#endif

#if 0
static void va_test_va(const char *format, ...)
{
	va_list args;
	va_start(args, format);

	va_arg(args, int);
/*
	puts(ua_pbx(gbuf, va_arg(args, char)));
	puts(ua_phx(gbuf, va_arg(args, short)));
	puts(ua_pbx(gbuf, va_arg(args, char)));
	puts(ua_phx(gbuf, va_arg(args, short)));
	puts(ua_pwx(gbuf, va_arg(args, int)));

	puts(ua_pgx(gbuf, va_arg(args, double)));
	puts(ua_pgx(gbuf, va_arg(args, double)));
	puts(ua_pgx(gbuf, va_arg(args, double)));
	puts(ua_pgx(gbuf, va_arg(args, double)));
	puts(ua_pgx(gbuf, va_arg(args, double)));
	puts(ua_pgx(gbuf, va_arg(args, double)));
	puts(ua_pgx(gbuf, va_arg(args, double)));
	puts(ua_pgx(gbuf, va_arg(args, double)));

	puts(ua_pwx(gbuf, va_arg(args, int)));
	puts(ua_phx(gbuf, va_arg(args, int)));
	puts(ua_pgx(gbuf, va_arg(args, int)));
	puts(ua_phx(gbuf, va_arg(args, int)));

	puts(ua_pgx(gbuf, va_arg(args, double)));
	puts(ua_pgx(gbuf, va_arg(args, double)));

	puts(ua_pgx(gbuf, va_arg(args, int)));
*/

	va_end(args);
}
#endif


static void test12()
{
	char c = 0x1;
	short s = 0x2;
	int i = 0x3;
	long l = 0x4;
	char* p = (char*)0x5;
	double d = 0x6;
	double d2 = 0xaa;
	float f = 0x7;

/*
	puts(ua_pbx(gbuf, va_test_raw("",
		c, s, c, s, 0xff,
		d, d, d, f, d, d, d, d2,
		0xee, s, l, 0xbb,
		(double)0x9999,
		(double)0x7777,
		0x1234
	)));
*/
/*
	puts("[va_test]");
	va_test_va("",
		c, s, c, s, 0xff,
		d, d, d, f, d, d, d, d2,
		0xee, s, l, 0xbb,
		(double)0x9999,
		(double)0x7777,
		0x1234
	);
*/
}

static void test13()
{
	puts(ua_pwx(gbuf, atoi("10")));
	puts(ua_pwx(gbuf, atoi("-10")));
	puts(ua_pgx(gbuf, ua_atoul("10")));
	puts(ua_pgx(gbuf, ua_atoul("-10")));

	puts("* 1");
	puts(ua_pwx(gbuf, atoi("4294967295")));		// UI max
	puts(ua_pwx(gbuf, atoi("4294967296")));

	puts("* 2");
	puts(ua_pgx(gbuf, ua_atoul("4294967295")));		// UI max
	puts(ua_pgx(gbuf, ua_atoul("4294967296")));

	puts("* 3");
	puts(ua_pgx(gbuf, ua_atoul("18446744073709551615")));	// UL max
	puts(ua_pgx(gbuf, ua_atoul("18446744073709551616")));

	//

	puts(ua_itoa( 2147483647, gbuf));
	puts(ua_itoa(-2147483648, gbuf));		// -2147483648: min neg
	puts(ua_itoa(-1234, gbuf));
	puts(ua_itoa( 1234, gbuf));
	puts(ua_itoa(-1, gbuf));
	puts(ua_itoa( 0, gbuf));
	puts(ua_itoa(-0, gbuf));
}

static void test14()
{
	//puts(ua_ltoa( 18446744073709551615, gbuf));
	puts(ua_ltoa( 9223372036854775807, gbuf));
	puts(ua_ltoa(-9223372036854775807, gbuf));
	puts(ua_ltoa( 2147483647, gbuf));
	puts(ua_ltoa(-2147483648, gbuf));		// -2147483648: min neg
	puts(ua_ltoa(-1234, gbuf));
	puts(ua_ltoa( 1234, gbuf));
	puts(ua_ltoa(-1, gbuf));
	puts(ua_ltoa( 0, gbuf));
	puts(ua_ltoa(-0, gbuf));
}

static void test15()
{
	const char format[] = "%lx";

	const int n1 = sprintf(NULL, format, -1L);
	const int n2 = sprintf(gbuf,  format, -1L);

	puts(gbuf);

	printf("n1 = %d\n", n1);
	printf("n2 = %d\n", n2);

	assert(n1 >= n2);
}

static void test16(int a, int b)
{
	char buf[96] = { 0 };

	memset(buf, '_', sizeof(buf) - 1);

	const void *prev = ua_getsp();
	void *s = alloca(16);
	memset(s, 'A', 16);

	const void *post = ua_getsp();
	ua_setsp(prev);
	const void *last = ua_getsp();

	assert(prev > s);
	assert(s == post);
	assert(prev == last);

	printf("prev=%p\n", prev);
	printf("s   =%p\n", s);
	printf("post=%p\n", post);
	printf("last=%p\n", last);

	//
	memset(buf, '_', sizeof(buf) - 1);
	ua_pgx(buf + 10, -1);
	puts(buf);
	puts(buf + strlen(buf) + 1);

	memset(buf, '_', sizeof(buf) - 1);
	ua_pwx(buf + 10, -1);
	puts(buf);
	puts(buf + strlen(buf) + 1);

	memset(buf, '_', sizeof(buf) - 1);
	ua_pbx(buf + 10, -1);
	puts(buf);
	puts(buf + strlen(buf) + 1);
}

static void test17()
{
	printf("%u %lu\n", -1, -1UL);

	puts(ua_itoa(-1, gbuf));
	puts(ua_itoa(-2147483640, gbuf));
	puts(ua_uitoa(-1, gbuf));

	puts(ua_ltoa(-1L, gbuf));
			//   12345678901234567890
	puts(ua_ltoa(-9223372036854775800L, gbuf));
	puts(ua_ultoa(-1L, gbuf));

	printf("%c\n", 'a');
	printf("%p %p\n", *test17, NULL);
}

static void test18()
{
	int dat[] = { 0, 1, -1 };

	for (int i=0; i<( sizeof(dat)/sizeof(dat[0]) ); i++)
	{
		puts(ua_pbx(gbuf, dat[i]));
		puts(ua_phx(gbuf, dat[i]));
		puts(ua_pwx(gbuf, dat[i]));
		puts(ua_pgx(gbuf, dat[i]));

		puts(ua_pbx0(gbuf, dat[i]));
		puts(ua_phx0(gbuf, dat[i]));
		puts(ua_pwx0(gbuf, dat[i]));
		puts(ua_pgx0(gbuf, dat[i]));
	}
}

static void test19()
{

	for (int i=0; i<10; i++)
	{
		const int rnd = rand();
		printf("%d) %d %d\n", i, rnd, rnd % 100);
	}

	puts("*");

	time_t t;
	time(&t);

	srand(t);

	for (int i=0; i<10; i++)
	{
		const int rnd = rand();
		printf("%d) %d %d\n", i, rnd, rnd % 100);
	}
	
}

static void test20()
{
	time_t t;
	time(&t);

	srand(t);

	void *arr[20] = { 0 };
	int narr = sizeof(arr) / sizeof(arr[0]);

	printf("now=%ld, narr=%d\n", t, narr);

	for (int j=0; j<narr; j++)
	{
		for (int i=0; i<narr; i++)
		{
			int pos = rand() % narr;

			if (arr[pos])
			{
				free(arr[pos]);
				arr[pos] = NULL;
			}
			else
			{
				size_t size = (rand() % 10240) + 3;

				char *p = malloc(size);
				sprintf(p, "%d", i);

				arr[pos] = p;
			}
		}
	}

	uc_walk_heap(cb_free, cb_alloc);

	puts("*");

	for (int i=0; i<narr; i++)
	{
		if (arr[i])
		{
			free(arr[i]);
			arr[i] = NULL;
		}
	}

	uc_walk_heap(cb_free, cb_alloc);

	puts("*");
}

static void test21()
{
	void* arr[10] = { 0 };

	for (int i=0; i<(sizeof(arr) / sizeof(arr[0])); i++)
	{
		arr[i] = uc_aprintf("%d", i);
	}

	uc_walk_heap(cb_free, cb_alloc);
	puts("*");

	// ----------------------------------------------

	free(arr[8]); arr[8] = NULL;

	uc_walk_heap(cb_free, cb_alloc);
	puts("* free(8)");
	puts("----------------");

	// ----------------------------------------------

	free(arr[5]); arr[5] = NULL;

	uc_walk_heap(cb_free, cb_alloc);
	puts("* free(5)");
	puts("----------------");

	// ----------------------------------------------

	const int idx = 4;

	void *op = arr[idx];
	void *np = realloc(op, 17);

	printf("%p:%p\n", op, np);
	arr[idx] = np;

	uc_walk_heap(cb_free, cb_alloc);
	puts("* realloc");
	puts("----------------");

	// ----------------------------------------------

	for (int i=0; i<(sizeof(arr) / sizeof(arr[0])); i++)
	{
		free(arr[i]);
	}

	uc_walk_heap(cb_free, cb_alloc);
}

static void test22()
{
				//0123456789012345678901234567890
	strcpy(gbuf, "          abc           ");
	puts(memcpy(gbuf + 3, gbuf + 10, 3));
	puts(gbuf);

	strcpy(gbuf, "          abc           ");
	puts(memcpy(gbuf + 11, gbuf + 10, 3));
	puts(gbuf);

	strcpy(gbuf, "          abc           ");
	puts(memcpy(gbuf + 9, gbuf + 10, 3));
	puts(gbuf);

	//
	strcpy(gbuf, "          abc           ");
	puts(memmove(gbuf + 11, gbuf + 10, 3));
	puts(gbuf);

	strcpy(gbuf, "          abc           ");
	puts(memmove(gbuf + 10, gbuf + 10, 3));
	puts(gbuf);

	strcpy(gbuf, "          abc           ");
	puts(memmove(gbuf + 9, gbuf + 10, 3));
	puts(gbuf);
}

jmp_buf jmpbuf;

static void test23()
{
	int r = setjmp(jmpbuf);

	if (r == 0)
	{
		longjmp(jmpbuf, 100);
	}
	else
	{
		printf("r=%d\n", r);
	}
}

#ifdef __clang__
int getval(int index)
{
	int r = 0;

	void *labels[] = {
		&&LABEL0,
		&&LABEL1,
		&&LABEL2,
		&&LABEL3,
	};

	goto *labels[index];

LABEL3: r++;
LABEL2: r++;
LABEL1: r++;
LABEL0:
	return r;
}
#endif

static void test24()
{
#ifndef __clang__
	int getval(int index)
	{
		int r = 0;

		void *labels[] = {
			&&LABEL0,
			&&LABEL1,
			&&LABEL2,
			&&LABEL3,
		};

		goto *labels[index];

LABEL3: r++;
LABEL2: r++;
LABEL1: r++;
LABEL0:
		return r;
	}
#endif

	for (int i=0; i<4; i++)
	{
		printf("%d=%d\n", i, getval(i));
	}
}

static void test25()
{
	void *ip = ua_getip();
	printf("ip=%p\n", ip);

	const void* s0 = ua_getsp();
	const void* d0 = alloca(0);
	const void* s1 = ua_getsp();
	const void* d1 = alloca(16);
	const void* s2 = ua_getsp();
	ua_setsp(s1);
	const void* s3 = ua_getsp();

	assert(s0 == s1);
	assert(s1 > d1);
	assert((s1 - d1) == 16);

	printf("s0=%p\nd0=%p\ns1=%p\nd1=%p\ns2=%p\ns3=%p\n", s0, d0, s1, d1, s2, s3);
}


extern void ua_test(long);

int main(int argc, char** argv, char** envs)
{
	//extern void __stack_chk_fail();
	//__stack_chk_fail();

#if 0
	test10(1, 2, 3);
	//test25();
	//test16(1, 2);

#else
	ua_test(-1);
	ua_test(-1L);

	for (int i=0; i<argc; i++) {
		printf("argv[%d] = '%s'\n", i, argv[i]);
	}

	unsigned long entry = (unsigned long)auxv_data.entry;
	unsigned long range = (void *)&etext - auxv_data.entry;
	printf("%p - %p = %lu\n", &etext, auxv_data.entry, range);

	puts("|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 1");
	test01();
	puts("|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 2");
	test02();
	puts("|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 3");
	test03();
	puts("|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 4");
	test04();
	puts("|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 5");
	test05();
	puts("|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 6");
	test06();
	puts("|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 7");
	test07();
	puts("|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 8");
	test08();
	puts("|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 9");
	test09();
	puts("|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 10");
	test10(1, 2, 3);

 #ifdef USE_BT
	puts("|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 11");
	test11();
 #endif

	puts("|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 12");
	test12();
	puts("|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 13");
	test13();
	puts("|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 14");
	test14();
	puts("|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 15");
	test15();
	puts("|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 16");
	test16(1, 2);
	puts("|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 17");
	test17();
	puts("|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 18");
	test18();
	puts("|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 19");
	test19();
	puts("|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 20");
	test20();
	puts("|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 21");
	test21();
	puts("|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 22");
	test22();
	puts("|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 23");
	test23();
	puts("|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 24");
	test24();
	puts("|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 25");
	test25();
#endif

	puts("|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ done");

	return 2;
}

// EOF
