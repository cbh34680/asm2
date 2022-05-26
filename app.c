#include <defs.h>

static void test()
{
	char haystack[] = "Abfhi\0aBc";

	const void* mem1 = _s_memchr(haystack, 'f', 9);
	const void* mem2 = _s_memchr(haystack, 'B', 9);
	const void* mem3 = _s_memchr(haystack, 'i', 9);
	_c_puts(mem1 ? mem1 : "NULL");
	_c_puts(mem2 ? mem2 : "NULL");
	_c_puts(mem3 ? mem3 : "NULL");

	const char* pos1 = _s_strchr(haystack, 'b');
	const char* pos2 = _s_strchr(haystack, 'B');
	_c_puts(pos1 ? pos1 : "NULL");
	_c_puts(pos2 ? pos2 : "NULL");

	const void* s1 = _s_getstack();
	char* buf = _s_alloca(16);
	const void* s2 = _s_getstack();

	_s_memset(buf, '@', 15);
	buf[15]= '\0';

	_c_puts("123456789012345678901234567890");
	_c_puts(buf);

	// https://qiita.com/EqualL2/items/168e083caa5f07a1105b

	int x = _c_log10(255) + 1;
}

static void test2(const char* s)
{
	char sz[100];

	_s_memset(sz, '\0', sizeof sz);
	_c_strcpy(sz, "abcde");
	char* d0 = _s_memmove(sz + 2, sz, 2);
	_c_puts(sz);
	_c_puts(d0);

	_s_memset(sz, '-', sizeof sz);
	char* d1 = _s_memmove(sz, s, _s_strlen(s) + 1);
	_c_puts(sz);
	_c_puts(d1);

	_s_memset(sz, '-', sizeof sz);
	char* d2 = _s_memcpy(sz, s, _s_strlen(s) + 1);
	_c_puts(sz);
	_c_puts(d2);

	_s_memset(sz, '-', sizeof sz);
	char* d3 = _c_strcpy(sz, s);
	_c_puts(sz);
	_c_puts(d3);
}

void test3()
{
	int fd =_s_open("/home/user/asm/a.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);

	_s_close(fd);

	int x;
	x = 55;
}

static void parse_auxv(const Elf64_auxv_t* auxv);

int main(int argc, char** argv, char** envs)
{
	for (int i=0; i<argc; i++) {
		_c_puts(argv[i]);
	}

	char* const* env = envs;
	while (*env++)
		;

	parse_auxv((Elf64_auxv_t*)env);

	test();
	test2("ABCDE");
	test3();

	return 2;
}

static void parse_phdrs(const Elf64_Phdr* phdr);

static void parse_auxv(const Elf64_auxv_t* auxv)
{
	const Elf64_Ehdr* sysi_ehdr = NULL;
	const Elf64_Phdr* main_phdr = NULL;

	Elf64_Half phent = 0;
	Elf64_Half phnum = 0;

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

			case AT_PHENT:
				phent = (Elf64_Half)auxv->a_un.a_val;
				break;

			case AT_PHNUM:
				phnum = (Elf64_Half)auxv->a_un.a_val;
				break;

			case AT_EXECFN:
				_c_print("AT_EXECFN=");
				_c_puts((char*)auxv->a_un.a_val);
				break;
		}
	}

	_c_puts("## sysi");
	assert(sysi_ehdr);

	assert(sysi_ehdr->e_ident[0] == 0x7f
		&& sysi_ehdr->e_ident[1] == 'E'
		&& sysi_ehdr->e_ident[2] == 'L'
		&& sysi_ehdr->e_ident[3] == 'F');

	const Elf64_Phdr* sysi_phdr = (Elf64_Phdr*)&sysi_ehdr[1];
	parse_phdrs(sysi_phdr);

	_c_puts("## main");
	assert(main_phdr);

	const Elf64_Ehdr* main_ehdr = (Elf64_Ehdr*)((void*)main_phdr - sizeof(Elf64_Ehdr));

	assert(main_ehdr->e_ident[0] == 0x7f
		&& main_ehdr->e_ident[1] == 'E'
		&& main_ehdr->e_ident[2] == 'L'
		&& main_ehdr->e_ident[3] == 'F');

	parse_phdrs(main_phdr);
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
