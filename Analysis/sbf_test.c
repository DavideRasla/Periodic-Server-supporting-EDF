#include <stdlib.h>
#include <stdio.h>

#include "sbf.h"

int main(int argc, char *argv[])
{
  unsigned int q, t, s;

  if (argc < 3) {
    fprintf(stderr, "Usage: %s <Q> <T>\n", argv[0]);

    return -1;
  }
  q = atoi(argv[1]);
  t = atoi(argv[2]);

  for (s = 0; s < 100; s++) {
    printf("%u %u\n", s, sbf(q, t, s));
  }

  return 0;
}
