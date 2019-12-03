#include "task.h"
#include "taskset.h"
#include "dbf.h"

static unsigned int my_ceil(unsigned int n, unsigned int d)
{
  unsigned int q;

  q = n / d;
  if (q * d == n) return q;
  return q + 1;
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

unsigned int dbf(const struct taskset *ts, unsigned int n, unsigned int t)
{
  unsigned int i;
  unsigned int res;

  res = 0;
  for (i = 0; i <= n; i++) {
    res += my_ceil(t, ts->tasks[i].p) * ts->tasks[i].c; 
  }

  return res;
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
