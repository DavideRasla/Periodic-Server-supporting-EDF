#include <stdio.h>
#include "task_io.h"
#include "dbf.h"
#include "task.h"
#include "taskset.h"
#include <stdio.h>
#include <math.h>
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

      printf("T%d has %d scheduling points: ", i, n);
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



void printDset(){

   
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

  printf("Is schedulable with RM ? : %d\n", check(ts));
  //printf("Is schedulable with EDF ? : %d\n", check_with_EDF(ts));
  printf("EDF ANALYSIS:\n");
  printf("U = %f\n", CalcU(ts));
  printf("L* = %d\n", CalcLSTAR(ts));
  printf("H = %d\n", CalcH(ts));
  printf("D set: { ");
int t[128];
int  n = D_Set_EFT(ts, 0, t, 128);

    if (n > 0) {
      unsigned int j;
      for (j = 0; j < (unsigned int)n; j++) {
        printf(" %u", t[j]);
      }
    printf("}\n");
    }
  printf("Is schedulable? :%d\n", check_EDF(ts,0));
  return 0;
}
