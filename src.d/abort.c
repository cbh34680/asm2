#include <defs.h>

void _u_easy_abort(
	const char *assertion, const char *file,
	unsigned int line, const char *function)
{
	_u_puts_e("### Abort. ###");

	_u_puts_e(assertion);
	_u_puts_e(file);
	_u_puts_e(function);

	_s_exit(120);
}

