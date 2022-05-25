#include <defs.h>

char *_c_strcpy(char *dest, const char *src)
{
	return (char*)_s_memcpy(dest, src, _s_strlen(src) + 1);
}

