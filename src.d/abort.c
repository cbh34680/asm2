#include <defs.h>

void _c_easy_abort(const char *assertion, const char *file,
 unsigned int line, const char *function)
{
	_c_puts_E("### Abort. ###");

	_c_puts_E(assertion);
	_c_puts_E(file);
	_c_puts_E(function);

	_s_exit(120);
}

