#include <stds.h>

void *uo_curbrk;

int brk(void *request)
{
	void *newbrk = syscall_brk(request);

	if (newbrk < request)
	{
		errno = ENOMEM;
		return -1;
	}

	uo_curbrk = newbrk;

	return 0;
}

void *sbrk(intptr_t increment)
{
	if (! uo_curbrk)
	{
		uo_curbrk = syscall_brk(0);
	}

	if (increment == 0)
	{
		return uo_curbrk;
	}

	void *oldbrk = uo_curbrk;

	int rc = brk(uo_curbrk + increment);
	if (rc != 0)
	{
		return (void*)-1;
	}

	return oldbrk;
}

