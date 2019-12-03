#include <stdlib.h>
#include <stdio.h>

#include "task.h"
#include "taskset.h"
#include "task_io.h"

#define MAX_TASKS 32

struct taskset *ts_load(FILE *f)
{
  struct taskset *ts;
  unsigned int i = 0;

  ts = malloc(sizeof(struct taskset));
  if (ts == NULL) {
    return NULL;
  }
  ts->tasks = malloc(sizeof(struct task) * MAX_TASKS);
  if (ts->tasks == NULL) {
    free(ts);

    return NULL;
  }

  while(!feof(f) && (i < MAX_TASKS)) {
    int res;

    res = fscanf(f, "%u %u %u\n", &ts->tasks[i].c, &ts->tasks[i].d, &ts->tasks[i].p);
    if (res == 3) {
      i++;
    }
  }

  ts->size = i;

  return ts;
}

void ts_print(const struct taskset *ts, FILE *f)
{
  unsigned int i;

  for (i = 0; i < ts->size; i++) {
    fprintf(f, "(%u, %u, %u)\n", ts->tasks[i].c, ts->tasks[i].d, ts->tasks[i].p);
  }
}
