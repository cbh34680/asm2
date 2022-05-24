#include "defs.h"

int _c_puts(const char* s)
{
	const size_t len = _s_strlen(s);

	ssize_t nw = _s_write(FD_STDOUT, s, len);
	nw += _s_write(FD_STDOUT, "\n", 1);

	return (int)nw;
}

