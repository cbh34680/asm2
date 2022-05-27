#include <defs.h>

void _u_easy_abort(
	const char *assertion, const char *file,
	unsigned int line, const char *function)
{
	_u_puts_E("### Abort. ###");

	_u_puts_E(assertion);
	_u_puts_E(file);
	_u_puts_E(function);

	_s_exit(120);
}

