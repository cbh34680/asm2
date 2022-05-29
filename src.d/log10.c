#include <stds.h>

// https://hiroyukichishiro.com/log-log2-log10-log1p-functions-in-c-language/

#define DBL_EXPONENT_MASK  0x7ffULL
#define DBL_EXPONENT_SHIFT 52ULL
#define DBL_EXPONENT_EMIN  1022ULL
 
#define FLT_EXPONENT_MASK  0xffUL
#define FLT_EXPONENT_SHIFT 23UL
#define FLT_EXPONENT_EMIN  126UL
 
#define LDBL_EXPONENT_MASK  0x7fffULL
#define LDBL_EXPONENT_EMIN  16382ULL
 
static double myfrexp(double x, int *exp)
{
  union {
    double d;
    long l;
  } y = {x};
 
  if (x == 0.0) {
    *exp = 0;
    return 0;
  }
 
  *exp = ((y.l >> DBL_EXPONENT_SHIFT) & DBL_EXPONENT_MASK) - DBL_EXPONENT_EMIN;
  y.l &= ~(DBL_EXPONENT_MASK << DBL_EXPONENT_SHIFT);
  y.l |= DBL_EXPONENT_EMIN << DBL_EXPONENT_SHIFT;
 
  return y.d;
}

static double myldexp(double x, int exp)
{
  union {
    double d;
    long l;
  } y = {x};
 
  if (x == 0.0) {
    return 0.0;
  }
 
  exp += (y.l >> DBL_EXPONENT_SHIFT) & DBL_EXPONENT_MASK;
 
  if (exp <= 0) {
    return 0;
  }
 
  if (exp >= DBL_EXPONENT_MASK) {
    errno = ERANGE;
 
    if (x < 0.0) {
      return (double)-HUGE_VAL;
    }
 
    return (double)HUGE_VAL;
  }
 
  y.l &= ~(DBL_EXPONENT_MASK << DBL_EXPONENT_SHIFT);
  y.l |= (long) exp << DBL_EXPONENT_SHIFT;
  return y.d;
}

#define LOG2 0.6931471805599453094172321214581765680755L
#define SQRT2 1.41421356237309504880168872421L
 
static double mylog(double x)
{
  int i, k;
  double x2, s, last;
 
  if (x <= 0.0) {
    //fprintf(stderr, "mylog(x): x <= 0.0\n");
    return -NAN;
  }
 
  myfrexp(x / SQRT2, &k);
 
  x /= myldexp(1.0, k);
  x = (x - 1.0) / (x + 1.0);
  x2 = x * x;
  i = 1;
  s = x;
 
  do {
    x *= x2;
    i += 2;
    last = s;
    s += x / i;
  } while (last != s);
 
  return LOG2 * k + 2.0 * s;
}

//double mylog10(double x)
double log10(double x)
{
  return mylog(x) / mylog(10.0);
}

