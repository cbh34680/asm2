#include <stds.h>

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

}

int main(int argc, char** argv, char** envs)
{
	for (int i=0; i<argc; i++) {
		uc_prints("argv=");
		puts(argv[i]);
	}

	test1();
	test2();
	test3();
	test4();
	test5();

	return 2;
}

// EOF
