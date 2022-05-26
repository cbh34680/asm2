#include <defs.h>

static ssize_t _c_dprint(int fd, const char* s)
{
	return _s_write(fd, s, _s_strlen(s));
}

ssize_t _c_print(const char* s)
{
	return _c_dprint(FD_STDOUT, s);
}

ssize_t _c_print_E(const char* s)
{
	return _c_dprint(FD_STDERR, s);
}

static const char LF = '\n';

int _c_puts(const char* s)
{
	ssize_t nw = _c_print(s);
	nw += _s_write(FD_STDOUT, &LF, 1);

	return (int)nw;
}

int _c_puts_E(const char* s)
{
	ssize_t nw = _c_print_E(s);
	nw += _s_write(FD_STDERR, &LF, 1);

	return (int)nw;
}

