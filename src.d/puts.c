#include <defs.h>

ssize_t _c_print(const char* s)
{
	const size_t len = _s_strlen(s);

	return _s_write(FD_STDOUT, s, len);
}

int _c_puts(const char* s)
{
	ssize_t nw = _c_print(s);
	nw += _s_write(FD_STDOUT, "\n", 1);

	return (int)nw;
}

