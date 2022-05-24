
#define FD_STDOUT		(1)
#define EOF				(-1)

typedef unsigned long size_t;
typedef long ssize_t;

void _s_exit(int);
void *_s_memset(void *s, int c, size_t n);
size_t _s_strlen(const char *s);
ssize_t _s_write(int fd, const void *buf, size_t count);
void *_s_alloca(size_t size);
void *_s_getstack();

int _c_puts(const char* s);

