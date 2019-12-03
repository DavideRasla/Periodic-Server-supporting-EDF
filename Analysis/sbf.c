#include "sbf.h"

unsigned int sbf(unsigned int q, unsigned int t, unsigned int s)
{
  unsigned int n;

  if (s < 2 * (t - q)) return 0;
  s -= 2 * (t - q);
  n = s / t;
  s = s % t;

  if (s > q) return (n + 1) * q;
  return n * q + s; 
}
