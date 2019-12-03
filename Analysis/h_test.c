#include <stdlib.h>
#include <stdio.h>

#include "task_io.h"
#include "dbf.h"
#include "sbf.h"

static void h_print(struct taskset *ts, unsigned int q_s, unsigned int t_s)
{
  unsigned int t[128];
  int n;
  unsigned int i;
  int schedulable;

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
      schedulable = 0;
      for (j = 0; j < (unsigned int)n; j++) {
        printf("\t%u -> dbf = %u; sbf = %u\n", t[j], dbf(ts, i, t[j]), sbf(q_s, t_s, t[j]));
        if (dbf(ts, i, t[j]) <= sbf(q_s, t_s, t[j])) schedulable = 1;
      }
      printf("\t\tSchedulable: %d\n", schedulable);
    }
    i++;
  }
}


int main(int argc, char *argv[])
{
  FILE *in;
  struct taskset *ts;
  unsigned int q, t;

  if (argc < 4) {
    fprintf(stderr, "Usage: %s <taskset> <Q> <T>\n", argv[0]);

    return -1;
  }

  in = fopen(argv[1], "r");
  if (in == NULL) {
    perror("FOpen");

    return -2;
  }
  q = atoi(argv[2]);
  t = atoi(argv[3]);

  ts = ts_load(in);
  if (ts == NULL) {
    fprintf(stderr, "Error loading taskset!\n");

    return -3;
  }
  printf("Taskset:\n");
  ts_print(ts, stdout);
  h_print(ts, q, t);

  return 0;
}

