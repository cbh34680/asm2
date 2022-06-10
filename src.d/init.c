#include <stds.h>

__huge_val_t __huge_val = { __HUGE_VAL_bytes };
int errno = 0;

extern int main(int argc, char** argv, char** envp);

static void parse_auxv(const Elf64_auxv_t* auxv);
static void parse_phdrs(const Elf64_Phdr* phdr);

int uc_init(int argc, char** argv, char** envp)
{
	char* const* env = envp;
	while (*env++)
		;

	parse_auxv((Elf64_auxv_t*)env);

	return main(argc, argv, envp);
}

struct auxv_data_type auxv_data;

static void parse_auxv(const Elf64_auxv_t* auxv)
{
	const Elf64_Ehdr* sysi_ehdr = NULL;
	const Elf64_Phdr* main_phdr = NULL;
	size_t pagesz = -1;
	void *entry = NULL;

	for (; auxv->a_type != AT_NULL; auxv++)
	{
		switch (auxv->a_type)
		{
			case AT_SYSINFO_EHDR:
				sysi_ehdr = (Elf64_Ehdr*)auxv->a_un.a_val;
				break;

			case AT_PHDR:
				main_phdr = (Elf64_Phdr*)auxv->a_un.a_val;
				break;

			case AT_PAGESZ:
				pagesz = (size_t)auxv->a_un.a_val;
				break;

			case AT_ENTRY:
				entry = (void *)auxv->a_un.a_val;
		}
	}

	assert(pagesz);

	if (sysi_ehdr)
	{
		//_c_puts("## sysi");
		assert(sysi_ehdr);

		assert(sysi_ehdr->e_ident[0] == 0x7f
			&& sysi_ehdr->e_ident[1] == 'E'
			&& sysi_ehdr->e_ident[2] == 'L'
			&& sysi_ehdr->e_ident[3] == 'F');

		const Elf64_Phdr* sysi_phdr = (Elf64_Phdr*)&sysi_ehdr[1];
		parse_phdrs(sysi_phdr);
	}

	//_c_puts("## main");
	assert(main_phdr);

	const Elf64_Ehdr* main_ehdr = (Elf64_Ehdr*)((void*)main_phdr - sizeof(Elf64_Ehdr));

	assert(main_ehdr->e_ident[0] == 0x7f
		&& main_ehdr->e_ident[1] == 'E'
		&& main_ehdr->e_ident[2] == 'L'
		&& main_ehdr->e_ident[3] == 'F');

	parse_phdrs(main_phdr);

	//
	auxv_data.sysi_ehdr = sysi_ehdr;
	auxv_data.main_phdr = main_phdr;
	auxv_data.pagesz = pagesz;
	auxv_data.entry = entry;
}

static void parse_phdrs(const Elf64_Phdr* phdr)
{
	for (; phdr->p_type != PT_NULL; phdr++)
	{
		switch (phdr->p_type)
		{
			case PT_LOAD:
			{
				break;
			}
		}
	}
}

// EOF
