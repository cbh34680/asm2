#include <defs.h>

static void test()
{
	char haystack[] = "abc";

	const char* pos1 = _s_strchr(haystack, 'b');
	_c_puts(pos1);

	const char* pos2 = _s_strchr(haystack, 'B');

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

	return 2;
}

