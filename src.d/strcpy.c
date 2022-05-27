#include <defs.h>

char *_c_strcpy(char *dest, const char *src)
{
	return (char*)_a_memcpy(dest, src, _a_strlen(src) + 1);
}

