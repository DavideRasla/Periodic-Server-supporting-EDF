#include "task.h"
#include "taskset.h"
#include "dbf.h"
#include <stdio.h>
static unsigned int my_ceil(unsigned int n, unsigned int d)
{
  unsigned int q;

  q = n / d;
  if (q * d == n) return q;
  return q + 1;
}
/*Deadline, t, and period*/
static unsigned int my_EDF_floor(unsigned int d ,unsigned int n, unsigned int p)
{
  unsigned int q;
//n sarebbe t
  int numeratore = n + p - d;
  if(numeratore < 0){
   numeratore = 0;
  }
  q = numeratore / p;
  if (q * d == n) return q;
  return (q == 0)?0:q - 1;//because we actually need for a floor op
}
int scheduling_points(const struct taskset *ts, unsigned int n, unsigned int *t, unsigned int size)
{
  unsigned int points, i;

  if (n >= ts->size) {
    return -1;
  }

  t[0] = ts->tasks[n].d;
  points = 1;
  for (i = 0; i < n; i++) {
    unsigned int j;

    j = 1;
    while (ts->tasks[i].p * j < t[0]) {
      if (points == size) return points;
      t[points] = ts->tasks[i].p * j;
      points = points + 1;
      j = j + 1;
    }
  } 

  return points;
}

unsigned int EDF_dbf(  struct taskset *ts,unsigned int n/*dimensione taskset*/, unsigned int t/*sched point*/)
{
  unsigned int i;
  unsigned int res;

  res = 0;
 
  for (i = 0; i <= n; i++) {
    printf("Taskset %d, my_EDF_Floor*CompTime is: %d\n", i, my_EDF_floor(ts->tasks[i].d, t, ts->tasks[i].p) * ts->tasks[i].c);
    res += my_EDF_floor(ts->tasks[i].d, t, ts->tasks[i].p) * ts->tasks[i].c; 
  }

  return res;
}


unsigned int dbf(const struct taskset *ts, unsigned int n, unsigned int t/*sched point*/)
{
  unsigned int i;
  unsigned int res;

  res = 0;
  for (i = 0; i <= n; i++) {
    res += my_ceil(t, ts->tasks[i].p) * ts->tasks[i].c; 
  }

  return res;
}

unsigned int check_EDF(const struct taskset *ts, unsigned int n)
{
  unsigned int sp[128];
  int n_sp, i;

  n_sp = scheduling_points(ts, n, sp, 128);

  for (i = 0; i < n_sp; i++) {
    if (EDF_dbf(ts, n, sp[i]) <= sp[i]) return 1;
  }

  return 0;
}


unsigned int check_n(const struct taskset *ts, unsigned int n)
{
  unsigned int sp[128];
  int n_sp, i;

  n_sp = scheduling_points(ts, n, sp, 128);

  for (i = 0; i < n_sp; i++) {
    if (dbf(ts, n, sp[i]) <= sp[i]) return 1;
  }

  return 0;
}

unsigned int check(const struct taskset *ts)
{
  return check_n(ts, ts->size - 1);
}

unsigned int check_with_EDF(const struct taskset *ts)
{
  return check_EDF(ts, ts->size - 1);
}


