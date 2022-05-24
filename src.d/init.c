#include <defs.h>

__huge_val_t __huge_val = { __HUGE_VAL_bytes };
int errno = 0;

extern int main(int argc, char** argv, char** envp);

int _c_init(int argc, char** argv, char** envp)
{
	return main(argc, argv, envp);
}

