struct task;
struct taskset;

struct taskset *ts_load(FILE *f);
void ts_print(const struct taskset *ts, FILE *f);
