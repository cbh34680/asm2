#include <defs.h>

static void test()
{
	char tmp[1024] = { 0 };

	const void* s1 = _s_getstack();

	char* buf = _s_alloca(16);

	const void* s2 = _s_getstack();

	_s_memset(buf, '@', 15);
	buf[15]= '\0';

	_c_puts("123456789012345678901234567890");
	_c_puts(buf);
}

int _c_init(int argc, char** argv, char** envs)
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

