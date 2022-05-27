#include <defs.h>

static ssize_t _u_dprint(int fd, const char* s)
{
	return _s_write(fd, s, _a_strlen(s));
}

ssize_t _u_print(const char* s)
{
	return _u_dprint(FD_STDOUT, s);
}

ssize_t _u_print_E(const char* s)
{
	return _u_dprint(FD_STDERR, s);
}

static const char _u_LF = '\n';

int _c_puts(const char* s)
{
	ssize_t nw = _u_print(s);
	nw += _s_write(FD_STDOUT, &_u_LF, 1);

	return (int)nw;
}

int _u_puts_E(const char* s)
{
	ssize_t nw = _u_print_E(s);
	nw += _s_write(FD_STDERR, &_u_LF, 1);

	return (int)nw;
}

