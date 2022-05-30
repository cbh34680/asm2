#include <stds.h>

#define PAGE_ALIGNED(v) ( ((v) + (auxv_data.pagesz - 1)) & ~(auxv_data.pagesz - 1) )


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

	const void* s1 = ua_getstack();
	char* buf = alloca(16);
	const void* s2 = ua_getstack();

	puts(ua_pgx(buf, (unsigned long)s1));
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

	char sz[100];

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

extern char edata, etext, end, __bss_start;

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
	uc_prints("brk=");
	puts(ua_pgx(buf, (unsigned long)brk(NULL)));
	uc_prints("sbrk=");
	puts(ua_pgx(buf, (unsigned long)sbrk(0)));
	uc_prints("sbrk=");
	puts(ua_pgx(buf, (unsigned long)sbrk(1)));
	uc_prints("sbrk=");
	puts(ua_pgx(buf, (unsigned long)sbrk(0)));
	uc_prints("sbrk=");
	puts(ua_pgx(buf, (unsigned long)sbrk(1)));
	uc_prints("sbrk=");
	puts(ua_pgx(buf, (unsigned long)sbrk(0)));
}

static void test8()
{
	char buf[64];

	for (int i=0; i<100; i++)
	{
		uc_prints("before=");
		uc_prints(ua_pgx(buf, (unsigned long)sbrk(0)));

		void *p = malloc(500);

		uc_prints(" after=");
		puts(ua_pgx(buf, (unsigned long)p));
	}
}

int main(int argc, char** argv, char** envs)
{
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

	return 2;
}

// EOF
