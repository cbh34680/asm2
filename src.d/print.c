#include <defs.h>

static ssize_t _uc_dprints(int fd, const char* s)
{
	return write(fd, s, _a_strlen(s));
}

ssize_t _uc_prints(const char* s)
{
	return _uc_dprints(FD_STDOUT, s);
}

ssize_t _uc_prints_e(const char* s)
{
	return _uc_dprints(FD_STDERR, s);
}

static const char _uo_LF = '\n';

int _c_puts(const char* s)
{
	ssize_t nw = _uc_prints(s);
	nw += write(FD_STDOUT, &_uo_LF, 1);

	return (int)nw;
}

int _uc_puts_e(const char* s)
{
	ssize_t nw = _uc_prints_e(s);
	nw += write(FD_STDERR, &_uo_LF, 1);

	return (int)nw;
}

