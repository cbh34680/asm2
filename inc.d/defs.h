
#define FD_STDOUT		(1)
#define EOF				(-1)

#define ERANGE			(34)
#define NAN				(0.0f / 0.0f)

#define NULL			((void*)0x0)

// https://sites.uclouvain.be/SystInfo/usr/include/bits/huge_val.h.html
typedef union { unsigned char __c[8]; double __d; } __huge_val_t;
#define __HUGE_VAL_bytes        { 0, 0, 0, 0, 0, 0, 0xf0, 0x7f }
//static __huge_val_t __huge_val = { __HUGE_VAL_bytes };
extern __huge_val_t __huge_val;
# define HUGE_VAL        (__huge_val.__d)

extern int errno;

typedef unsigned long size_t;
typedef long ssize_t;

void _s_exit(int);
void *_s_memset(void *s, int c, size_t n);
char* _s_strchr(const char *s, int c);
size_t _s_strlen(const char *s);
ssize_t _s_write(int fd, const void *buf, size_t count);
void *_s_alloca(size_t size);
void *_s_getstack();

int _c_puts(const char* s);
double _c_log10(double x);

