#include <stds.h>

char gbuf[1024];

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

	assert(s1 == d1);
	assert((s1 - s2) == 16);

	printf("s1=0x%lx d1=0x%lx s2=0x%lx\n");

	puts(memset(gbuf, ',', 15));
	gbuf[15]= '\0';

	puts("123456789012345678901234567890");
	puts(gbuf);

	// https://qiita.com/EqualL2/items/168e083caa5f07a1105b

	int n = 255;
	int x = log10(n) + 1;
	printf("log10(%d)+1 = %d\n", n, x);
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

	strcpy(gbuf, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	printf("0x[%lx]\n", -2);

	strcpy(gbuf, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	printf("0x[%x]\n", 12312312);

	strcpy(gbuf, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	printf("0x[%s]\n", ua_phx(gbuf, 143));
}

static void test5()
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

static void test6()
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

static void test7()
{
	printf("test7=%lx\n", test7);
	printf("etext=%lx\n", &etext);
	printf("global_data1=%lx\n", &global_data1);
	printf("global_data2=%lx\n", &global_data2);
	printf("edata=%lx\n", &edata);
	printf("__bss_start=%lx\n", &__bss_start);
	printf("global_bss1=%lx\n", &global_bss1);
	printf("global_bss2=%lx\n", &global_bss2);
	printf("end=%lx\n", &end);
}

static void prt_(const char *name, const void *pos)
{
	printf("[%s]\t\t%lx\n", name, pos);
}

#define prt(v) prt_(#v, (v))

static void cb_freep(const void *mem, size_t siz)
{
	printf("\tfreep: %lx, %lx\n", mem, siz);
}

static void cb_alloc(const void *mem, size_t siz)
{
	printf("\talloc: %lx, %lx\n", mem, siz);
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

	for (int i=0; i<20; i++, prev=curr)
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
	}
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

		printf("%lx\t%lx\n", caller, bp);
	}

	printf("0x%lx (%d)\n", bp-bp_first, bp-bp_first);
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

static void test16()
{
	char buf[96] = { 0 };

	memset(buf, '_', sizeof(buf) - 1);

	char *s = alloca(16);
	memset(s, 'A', 16);

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
	

int iii = 0;
}

extern void ua_test(long);

int main(int argc, char** argv, char** envs)
{
	//extern void __stack_chk_fail();
	//__stack_chk_fail();

	ua_test(-1);
	ua_test(-1L);

	for (int i=0; i<argc; i++) {
		printf("argv[%d] = '%s'\n", i, argv[i]);
	}

	puts("|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 1");
	test1();
	puts("|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 2");
	test2();
	puts("|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 3");
	test3();
	puts("|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 4");
	test4();
	puts("|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 5");
	test5();
	puts("|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 6");
	test6();
	puts("|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 7");
	test7();
	puts("|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 8");
	test8();
	puts("|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 9");
	test9();
	puts("|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 10");
	test10(1, 2, 3);
	puts("|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 11");
	test11();
	puts("|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 12");
	test12();
	puts("|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 13");
	test13();
	puts("|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 14");
	test14();
	puts("|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 15");
	test15();
	puts("|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 16");
	test16();

	return 2;
}

// EOF
