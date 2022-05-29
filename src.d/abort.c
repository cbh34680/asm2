#include <stds.h>

void uc_easy_abort(
	const char *assertion, const char *file,
	unsigned int line, const char *function)
{
	uc_puts_e("### Abort. ###");

	uc_puts_e(assertion);
	uc_puts_e(file);
	uc_puts_e(function);

	exit(120);
}

