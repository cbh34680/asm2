#include <stds.h>

char *strcat(char *dest, const char *src)
{
	strcpy(&dest[strlen(dest) - 1], src);

	return dest;
}

char *strcpy(char *dest, const char *src)
{
	return (char*)memcpy(dest, src, strlen(src) + 1);
}

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

int strcmp(const char *s1, const char *s2)
{
	return memcmp(s1, s2, strlen(s1) + 1);
}



