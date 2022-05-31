#include <stds.h>

static void *uo_brk;

int brk(void *request)
{
	void *newbrk = syscall_brk(request);

	if (newbrk < request)
	{
		errno = ENOMEM;
		return -1;
	}

	uo_brk = newbrk;

	return 0;
}

void *sbrk(intptr_t increment)
{
	if (! uo_brk)
	{
		uo_brk = syscall_brk(0);
	}

	if (increment == 0)
	{
		return uo_brk;
	}

	void *oldbrk = uo_brk;

	int rc = brk(uo_brk + increment);
	if (rc != 0)
	{
		return (void*)-1;
	}

	return oldbrk;
}

