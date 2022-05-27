#include <defs.h>

static void test()
{
	char haystack[] = "Abfhi\0aBc";

	const void* mem1 = _a_memchr(haystack, 'f', 9);
	const void* mem2 = _a_memchr(haystack, 'B', 9);
	const void* mem3 = _a_memchr(haystack, 'i', 9);

	_c_puts(mem1 ? mem1 : "NULL");
	_c_puts(mem2 ? mem2 : "NULL");
	_c_puts(mem3 ? mem3 : "NULL");

	const char* pos1 = _a_strchr(haystack, 'b');
	const char* pos2 = _a_strchr(haystack, 'B');

	_c_puts(pos1 ? pos1 : "NULL");
	_c_puts(pos2 ? pos2 : "NULL");

	const void* s1 = _a_getstack();
	char* buf = _a_alloca(16);
	const void* s2 = _a_getstack();

	_c_puts(_ua_pgx(buf, (unsigned long)s1));
	_c_puts(_ua_pgx(buf, (unsigned long)s2));

	_c_puts(_a_memset(buf, '@', 15));
	buf[15]= '\0';

	_c_puts("123456789012345678901234567890");
	_c_puts(buf);

	// https://qiita.com/EqualL2/items/168e083caa5f07a1105b

	int x = _c_log10(255) + 1;
}

static void test2()
{
	const char* s = "ABCDE";

	char sz[100];

	_c_puts(_c_strcpy(sz, "abcde"));
	_c_puts(_a_memmove(sz + 2, sz, 2));

	_a_memset(sz, '-', sizeof sz);
	_c_puts(_a_memmove(sz, s, _a_strlen(s) + 1));

	_a_memset(sz, '-', sizeof sz);
	_c_puts(_a_memcpy(sz, s, _a_strlen(s) + 1));

	_a_memset(sz, '-', sizeof sz);
	_c_puts(_c_strcpy(sz, s));
}

void test3()
{
	const int fd = open("/home/user/asm/a.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);

	close(fd);
}

void test4()
{
	char buf[256];

	_c_puts("   1234567890123456789");
	_c_puts("   0123456789012345678");

	_c_strcpy(buf, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	_uc_prints("0x[");
	_uc_prints(_ua_pgx(buf, -2));
	_c_puts("]");

	_c_strcpy(buf, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	_uc_prints("0x[");
	_uc_prints(_ua_pwx(buf, 2));
	_c_puts("]");

	_c_strcpy(buf, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	_uc_prints("0x[");
	_uc_prints(_ua_phx(buf, 5));
	_c_puts("]");
}

int main(int argc, char** argv, char** envs)
{
	for (int i=0; i<argc; i++) {
		_uc_prints("argv=");
		_c_puts(argv[i]);
	}

	test();
	test2();
	test3();
	test4();

	return 2;
}

// EOF
