#ifndef __DEF_H_INCLUDE__
#define __DEF_H_INCLUDE__

//
#define FD_STDIN		(0)
#define FD_STDOUT		(1)
#define FD_STDERR		(2)

#define EOF				(-1)

#define ENOMEM			(12)
#define ERANGE			(34)
#define NAN				(0.0f / 0.0f)

#define NULL			((void*)0x0)

// https://sites.uclouvain.be/SystInfo/usr/include/bits/huge_val.h.html
typedef union { unsigned char __c[8]; double __d; } __huge_val_t;
#define __HUGE_VAL_bytes        { 0, 0, 0, 0, 0, 0, 0xf0, 0x7f }
//static __huge_val_t __huge_val = { __HUGE_VAL_bytes };
extern __huge_val_t __huge_val;
# define HUGE_VAL        (__huge_val.__d)

// open - flags - fcntl.h
#define O_RDONLY        00000000
#define O_WRONLY        00000001
#define O_RDWR          00000002
#define O_CREAT         00000100        /* not fcntl */
#define O_EXCL          00000200        /* not fcntl */
#define O_NOCTTY        00000400        /* not fcntl */
#define O_TRUNC         00001000        /* not fcntl */
#define O_APPEND        00002000
#define O_NONBLOCK      00004000
#define O_DSYNC         00010000        /* used to be O_SYNC, see below */
#define O_DIRECT        00040000        /* direct disk access hint */
#define O_LARGEFILE     00100000
#define O_DIRECTORY     00200000        /* must be a directory */
#define O_NOFOLLOW      00400000        /* don't follow links */
#define O_NOATIME       01000000
#define O_CLOEXEC       02000000        /* set close_on_exec */
#define __O_SYNC        04000000
#define O_SYNC          (__O_SYNC|O_DSYNC)
#define O_PATH          010000000
#define __O_TMPFILE     020000000
#define O_TMPFILE (__O_TMPFILE | O_DIRECTORY)
#define O_TMPFILE_MASK (__O_TMPFILE | O_DIRECTORY | O_CREAT)
#define O_NDELAY        O_NONBLOCK

// open - mode - stat.h
#define S_IRWXU 00700
#define S_IRUSR 00400
#define S_IWUSR 00200
#define S_IXUSR 00100
#define S_IRWXG 00070
#define S_IRGRP 00040
#define S_IWGRP 00020
#define S_IXGRP 00010
#define S_IRWXO 00007
#define S_IROTH 00004
#define S_IWOTH 00002
#define S_IXOTH 00001

// x86_64-linux-gnu/bits/auxv.h
#define AT_NULL             0
#define AT_PHDR             3
#define AT_PHENT            4
#define AT_PHNUM            5
#define AT_PAGESZ           6
#define AT_BASE             7
#define AT_ENTRY            9
#define AT_EXECFN			31
#define AT_SYSINFO_EHDR     33

// x86_64-linux-gnu/bits/mman-linux.h
#define PROT_READ       0x1
#define PROT_WRITE      0x2
#define PROT_EXEC       0x4
#define PROT_NONE       0x0

// linux/mman.h
#define MAP_SHARED         0x01
#define MAP_PRIVATE        0x02
#define MAP_FIXED          0x10
#define MAP_ANONYMOUS      0x20
# define MAP_LOCKED     0x02000

// x86_64-linux-gnu/sys/mman.h
#define MAP_FAILED     ((void *) -1)


// stdint.h
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;
typedef long int off_t;

typedef long int intptr_t;

// linux/elf.h
typedef uint16_t Elf64_Half;
typedef uint32_t Elf64_Word;
typedef uint64_t Elf64_Addr;
typedef uint64_t Elf64_Off;
typedef uint64_t Elf64_Xword;

// time.h
typedef long int __time_t;
typedef __time_t time_t;

typedef struct
{
  uint64_t a_type;
  union
    {
      uint64_t a_val;
    } a_un;
} Elf64_auxv_t;

typedef struct
{
  unsigned char e_ident[(16)];
  Elf64_Half e_type;
  Elf64_Half e_machine;
  Elf64_Word e_version;
  Elf64_Addr e_entry;
  Elf64_Off e_phoff;
  Elf64_Off e_shoff;
  Elf64_Word e_flags;
  Elf64_Half e_ehsize;
  Elf64_Half e_phentsize;
  Elf64_Half e_phnum;
  Elf64_Half e_shentsize;
  Elf64_Half e_shnum;
  Elf64_Half e_shstrndx;
} Elf64_Ehdr;

typedef struct
{
  Elf64_Word p_type;
  Elf64_Word p_flags;
  Elf64_Off p_offset;
  Elf64_Addr p_vaddr;
  Elf64_Addr p_paddr;
  Elf64_Xword p_filesz;
  Elf64_Xword p_memsz;
  Elf64_Xword p_align;
} Elf64_Phdr;


#define PT_NULL			0
#define PT_LOAD			1
#define PT_DYNAMIC		2
#define PT_INTERP		3

typedef unsigned long size_t;
typedef long ssize_t;
typedef unsigned short mode_t;

// https://qiita.com/nori26/items/9ccef61571602a6a3b45

typedef struct
{
	unsigned int    gp_offset;          //???????????????????????????????????????
	unsigned int    fp_offset;          //????????????????????????????????????????????????
	void            *overflow_arg_area; //????????????????????????????????????
	void            *reg_save_area;     //??????????????????????????????????????????

	void            *_fp_save_area;
	void            *_end_reg_save_area;
	void            *_end_fp_save_area;

	size_t			_named_argc;
}
va_list[1];

//
typedef struct
{
	volatile unsigned long regs[8];
}
jmp_buf[1];

//
struct auxv_data_type
{
	Elf64_Ehdr const *sysi_ehdr;
	Elf64_Phdr const *main_phdr;
	size_t pagesz;
	void const *entry;
};

#endif
