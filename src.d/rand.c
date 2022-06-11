#include <stds.h>

// https://linuxjm.osdn.jp/html/LDP_man-pages/man3/rand.3.html

static unsigned long next = 1;

void srand(unsigned int seed)
{
	next = seed;
}

int rand(void)
{
	next = next * 1103515245 + 12345;

	return (unsigned)(next/65536) % 2147483647;
}

