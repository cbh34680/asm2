#include <stds.h>

char *strdup(const char *s)
{
	const size_t len = strlen(s);

	char* pdup = malloc(len + 1);
	if (! pdup)
	{
		return NULL;
	}

	return strcpy(pdup, s);
}

