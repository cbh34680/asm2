#include <defs.h>

void _uc_easy_abort(
	const char *assertion, const char *file,
	unsigned int line, const char *function)
{
	_uc_puts_e("### Abort. ###");

	_uc_puts_e(assertion);
	_uc_puts_e(file);
	_uc_puts_e(function);

	exit(120);
}

