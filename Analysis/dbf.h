int scheduling_points(const struct taskset *ts, unsigned int n, unsigned int *t, unsigned int size);
unsigned int dbf(const struct taskset *ts, unsigned int n, unsigned int t);
unsigned int check_n(const struct taskset *ts, unsigned int n);
unsigned int check(const struct taskset *ts);
float CalcU(struct taskset *ts);
int CalcLSTAR(struct taskset *ts);
int CalcH(struct taskset *ts);