#ifndef __STDS_H_INCLUDE__
#define __STDS_H_INCLUDE__

#include <defs.h>

// [1] system call
extern int syscall_close(int);
extern void syscall_exit(int);
extern int syscall_open(const char *pathname, int flags, mode_t mode);
extern ssize_t syscall_write(int fd, const void *buf, size_t count);
extern void* syscall_brk(void *addr);
extern time_t syscall_time(time_t *tloc);

#define close		syscall_close
#define exit		syscall_exit
#define open		syscall_open
#define write		syscall_write
#define time		syscall_time

// [2] std library - asm
extern void *alloca(size_t size);
extern int atoi(const char *nptr);
extern void *memchr(const void *s, int c, size_t n);
extern int memcmp(const void *s1, const void *s2, size_t n);
extern void *memcpy(void *dest, const void *src, size_t n);
extern void *memmove(void *dest, const void *src, size_t n);
extern void *memset(void *s, int c, size_t n);
extern char* strchr(const char *s, int c);
extern char *strdupa(const char *s);
extern size_t strlen(const char *s);

// [3] std library - c
extern int brk(void *addr);
extern void free(void *ptr);
extern double log10(double x);
extern void longjmp(jmp_buf env, int val);
extern void *malloc(size_t size);
extern int printf(const char *format, ...);
extern int puts(const char* s);
extern int rand(void);
extern void *realloc(void *ptr, size_t size);
extern int setjmp(jmp_buf env);
extern void srand(unsigned int seed);
extern char *strcat(char *dest, const char *src);
extern char *strcpy(char *dest, const char *src);
extern char *strdup(const char *s);
extern int strcmp(const char *s1, const char *s2);
extern void *sbrk(intptr_t increment);
extern int sprintf(char *str, const char *format, ...);
extern int vsprintf(char *str, const char *format, __builtin_va_list ap);

//extern int sprintf(const char *format, ...);
/*
extern void va_start_(va_list ap, void *last);
extern void va_end(va_list ap);
extern double va_arg_f(va_list ap);
extern unsigned long va_arg_i(va_list ap);

#define va_start(ap, last) va_start_((ap), &last)

#define va_arg(ap, type) (type)_Generic( \
 ((type) 0), double:va_arg_f, float:va_arg_f, default:va_arg_i)( (ap) )
*/


// [4] user func - asm
extern long ua_atoul(const char *nptr);
extern void *ua_bt_caller(int deep, void *bp);
extern void *ua_getip(void);
extern void *ua_getsp(void);
extern void ua_setsp(const void *newsp);
extern char *ua_itoa(int value, char *str);
extern char *ua_ltoa(long value, char *str);
extern char *ua_uitoa(unsigned int value, char *str);
extern char *ua_ultoa(unsigned long value, char *str);

extern char *ua_pgb(char *dest, const unsigned long src);
extern char *ua_pwb(char *dest, const unsigned int src);
extern char *ua_phb(char *dest, const unsigned short src);
extern char *ua_pbb(char *dest, const unsigned char src);
extern char *ua_pgb0(char *dest, const unsigned long src);
extern char *ua_pwb0(char *dest, const unsigned int src);
extern char *ua_phb0(char *dest, const unsigned short src);
extern char *ua_pbb0(char *dest, const unsigned char src);

extern char *ua_pgx(char *dest, const unsigned long src);
extern char *ua_pwx(char *dest, const unsigned int src);
extern char *ua_phx(char *dest, const unsigned short src);
extern char *ua_pbx(char *dest, const unsigned char src);
extern char *ua_pgx0(char *dest, const unsigned long src);
extern char *ua_pwx0(char *dest, const unsigned int src);
extern char *ua_phx0(char *dest, const unsigned short src);
extern char *ua_pbx0(char *dest, const unsigned char src);

// [5] user func - c
typedef _Bool (* uc_walk_callback)(const void *addr, size_t size, _Bool isfreep, const void *next);

extern char *uc_aprintf(const char *format, ...);
extern void uc_easy_abort(const char *assertion,
 const char *file, unsigned int line, const char *function);
extern void const *uc_get_base(int target);
extern void const *uc_get_freep(void);
extern ssize_t uc_prints(const char* s);
extern ssize_t uc_prints_e(const char* s);
extern int uc_puts_e(const char* s);
extern void const *uc_walk_freep(uc_walk_callback cb_free);
extern void const *uc_walk_heap(uc_walk_callback cb_free, uc_walk_callback cb_alloc);

//
#define assert(expr) \
 ( (expr) ? ((void)0) : uc_easy_abort(#expr, __FILE__, __LINE__, __func__) )

//
extern int errno;
extern struct auxv_data_type auxv_data;
extern char edata, etext, end, __bss_start;

#define PAGE_ALIGNED(v) ( ((size_t)(v) + (auxv_data.pagesz - 1)) & ~(auxv_data.pagesz - 1) )

#define BUS_SIZE		(16)
#define BUS_ALIGNED(v)  ( ((size_t)(v) + (BUS_SIZE - 1)) & ~(BUS_SIZE - 1) )

#define MAX(a, b) ( ((a) > (b)) ? (a) : (b) )


#endif

