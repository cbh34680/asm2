#include <stds.h>

static void test1()
{
	char buf[64];
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
	char buf[256];

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
	char buf[64];

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
	char buf[64];

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
	char buf[64];

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
	char buf[64];

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
	char buf[64];

	uc_prints("\tfreep: ");
	uc_prints(ua_pgx(buf, (unsigned long)mem));
	uc_prints(", ");
	puts(ua_pgx(buf, siz));
}

static void cb_alloc(const void *mem, size_t siz)
{
	char buf[64];

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
	char buf[64];

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
	char buf[64];

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
	char buf[64];

	for (int i=0; i<9999; i++)
	{
		void *p = ua_bt_caller(i);
		if (! p)
		{
			break;
		}

		puts(ua_pgx(buf, (unsigned long)p));
	}
}

static unsigned char foo(const char *a, ...)
{
	unsigned char al;
	__asm__ volatile("mov %0, %%al" : "=r"(al));
	//assert(al == 0);


	return al;
}

static void test12()
{
	char buf[64];

	char c = 0x11;
	short s = 0x22;
	int i = 0x33;
	long l = 0x44;
	char* p = 0x55;
	double d = 0x66;

	puts(ua_pbx(buf, foo("", c, s, i, l, p, c, s, i, l, p)));
	puts(ua_pbx(buf, foo("", c, s, i, d, p, c, s, i, d, p)));
	puts(ua_pbx(buf, foo("", d)));
	//puts(ua_pbx(buf, foo("", d)));

	//foo("aaa", "bbb", "ccc", "ddd", "eee", "fff", "000", "111", "222", "333", "444", "555");
}

int main(int argc, char** argv, char** envs)
{
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
