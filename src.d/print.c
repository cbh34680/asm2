#include <defs.h>

static ssize_t _u_dprints(int fd, const char* s)
{
	return write(fd, s, _a_strlen(s));
}

ssize_t _u_prints(const char* s)
{
	return _u_dprints(FD_STDOUT, s);
}

ssize_t _u_prints_e(const char* s)
{
	return _u_dprints(FD_STDERR, s);
}

static const char _u_LF = '\n';

int _c_puts(const char* s)
{
	ssize_t nw = _u_prints(s);
	nw += write(FD_STDOUT, &_u_LF, 1);

	return (int)nw;
}

int _u_puts_e(const char* s)
{
	ssize_t nw = _u_prints_e(s);
	nw += write(FD_STDERR, &_u_LF, 1);

	return (int)nw;
}

