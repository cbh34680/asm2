#include <defs.h>

static void test()
{
	char haystack[] = "Abfhi\0aBc";

	const void* mem1 = _s_memchr(haystack, 'f', 9);
	const void* mem2 = _s_memchr(haystack, 'B', 9);
	const void* mem3 = _s_memchr(haystack, 'i', 9);
	_c_puts(mem1 ? mem1 : "NULL");
	_c_puts(mem2 ? mem2 : "NULL");
	_c_puts(mem3 ? mem3 : "NULL");

	const char* pos1 = _s_strchr(haystack, 'b');
	const char* pos2 = _s_strchr(haystack, 'B');
	_c_puts(pos1 ? pos1 : "NULL");
	_c_puts(pos2 ? pos2 : "NULL");

	const void* s1 = _s_getstack();
	char* buf = _s_alloca(16);
	const void* s2 = _s_getstack();

	_s_memset(buf, '@', 15);
	buf[15]= '\0';

	_c_puts("123456789012345678901234567890");
	_c_puts(buf);

	// https://qiita.com/EqualL2/items/168e083caa5f07a1105b

	int x = _c_log10(255) + 1;
}

static void test2(const char* s)
{
	char sz[100];

	_s_memset(sz, '\0', sizeof sz);
	_c_strcpy(sz, "abcde");
	char* d0 = _s_memmove(sz + 2, sz, 2);
	_c_puts(sz);
	_c_puts(d0);

	_s_memset(sz, '-', sizeof sz);
	char* d1 = _s_memmove(sz, s, _s_strlen(s) + 1);
	_c_puts(sz);
	_c_puts(d1);

	_s_memset(sz, '-', sizeof sz);
	char* d2 = _s_memcpy(sz, s, _s_strlen(s) + 1);
	_c_puts(sz);
	_c_puts(d2);

	_s_memset(sz, '-', sizeof sz);
	char* d3 = _c_strcpy(sz, s);
	_c_puts(sz);
	_c_puts(d3);
}

void test3()
{
	int fd =_s_open("/home/user/asm/a.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);

	_s_close(fd);

	int x;
	x = 55;
}

int main(int argc, char** argv, char** envs)
{
	for (int i=0; i<argc; i++) {
		_c_puts(argv[i]);
	}

	char* const* pos = envs;
	while (*pos) {
		_c_puts(*pos);
		pos++;
	}

	test();
	test2("ABCDE");
	test3();

	return 2;
}

