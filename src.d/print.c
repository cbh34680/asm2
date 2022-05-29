#include <stds.h>

static ssize_t uc_dprints(int fd, const char* s)
{
	return write(fd, s, strlen(s));
}

ssize_t uc_prints(const char* s)
{
	return uc_dprints(FD_STDOUT, s);
}

ssize_t uc_prints_e(const char* s)
{
	return uc_dprints(FD_STDERR, s);
}

static const char uo_LF = '\n';

int puts(const char* s)
{
	ssize_t nw = uc_prints(s);
	nw += write(FD_STDOUT, &uo_LF, 1);

	return (int)nw;
}

int uc_puts_e(const char* s)
{
	ssize_t nw = uc_prints_e(s);
	nw += write(FD_STDERR, &uo_LF, 1);

	return (int)nw;
}

