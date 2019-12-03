#include <stdio.h>

#include "task_io.h"
#include "dbf.h"

static void stats_print(struct taskset *ts)
{
  unsigned int t[128];
  int n;
  unsigned int i;

  i = 0; n = 1;
  while(n > 0) {
    n = scheduling_points(ts, i, t, 128);
    if (n > 0) {
      unsigned int j;

      printf("T%d scheduling points (%d): ", i, n);
      for (j = 0; j < (unsigned int)n; j++) {
        printf(" %u", t[j]);
      }
      printf("\n");
      for (j = 0; j < (unsigned int)n; j++) {
        printf("\tdbf(%u) = %u\n", t[j], dbf(ts, i, t[j]));
      }
    }
    i++;
  }
}

int main(int argc, char *argv[])
{
  FILE *in;
  struct taskset *ts;

  if (argc < 2) {
    fprintf(stderr, "Usage: %s <taskset>\n", argv[0]);

    return -1;
  }

  in = fopen(argv[1], "r");
  if (in == NULL) {
    perror("FOpen");

    return -2;
  }

  ts = ts_load(in);
  if (ts == NULL) {
    fprintf(stderr, "Error loading taskset!\n");

    return -3;
  }
  printf("Taskset:\n");
  ts_print(ts, stdout);
  stats_print(ts);

  printf("Is schedulable: %d\n", check(ts));

  return 0;
}
