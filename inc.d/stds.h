#ifndef __STDS_H_INCLUDE__
#define __STDS_H_INCLUDE__

#include <defs.h>

// [1] system call
extern int close(int);
extern void exit(int);
extern int open(const char *pathname, int flags, mode_t mode);
extern ssize_t write(int fd, const void *buf, size_t count);
extern void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
extern int munmap(void *addr, size_t length);

// [2] std library - asm
extern void *alloca(size_t size);
extern int atoi(const char *nptr);
extern void *memchr(const void *s, int c, size_t n);
extern void *memcpy(void *dest, const void *src, size_t n);
extern void *memmove(void *dest, const void *src, size_t n);
extern void *memset(void *s, int c, size_t n);
extern char* strchr(const char *s, int c);
extern size_t strlen(const char *s);

// [3] std library - c
extern char *strcpy(char *dest, const char *src);
extern int puts(const char* s);
extern double log10(double x);

// [4] user func - asm
extern void *ua_getstack();
extern char *ua_xgx(char *dest, const unsigned long src);
extern char *ua_xwx(char *dest, const unsigned int src);
extern char *ua_xhx(char *dest, const unsigned short src);

// [5] user func - c
extern ssize_t uc_prints(const char* s);
extern ssize_t uc_prints_e(const char* s);
extern int uc_puts_e(const char* s);
extern void uc_easy_abort(const char *assertion, const char *file, unsigned int line, const char *function);

//
#define assert(expr) \
 ( (expr) ? ((void)0) : uc_easy_abort(#expr, __FILE__, __LINE__, __func__) )

//
extern int errno;
extern struct auxv_data_type auxv_data;

#endif
