#include "task.h"
#include "taskset.h"
#include "dbf.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int gcd(int a, int b) 
{ 
    if (b == 0) 
        return a; 
    return gcd(b, a % b); 
} 
int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}  
// Returns LCM of array elements 
int findlcm(int arr[], int n) 
{ 
    // Initialize result 
    int ans = arr[0]; 
  
    // ans contains LCM of arr[0], ..arr[i] 
    // after i'th iteration, 
    for (int i = 1; i < n; i++) 
        ans = (((arr[i] * ans)) / (gcd(arr[i], ans))); 
  
    return ans; 
}

float CalcU(struct taskset *ts)
{
   float res = 0;
 for (int i = 0; i < ts->size ; i++) {
    res += ((float)ts->tasks[i].c /  (float)ts->tasks[i].p); 
 }
 return res;
};
int CalcLSTAR(struct taskset *ts){
 float sum = 0;
 float res = 0;
 int maxDeadline = 0;
 for (int i = 0; i < ts->size ; i++) {
    sum += ((float)ts->tasks[i].p -  (float)ts->tasks[i].d)* ((float)ts->tasks[i].c /  (float)ts->tasks[i].p); //Somm (Ti - Di)*Ci 
    if(ts->tasks[i].d>maxDeadline)
      maxDeadline = ts->tasks[i].d;
 }
  
  res = sum/(1-CalcU(ts));
  
  return (res > maxDeadline)?res:maxDeadline;
 }
int CalcH(struct taskset *ts)
{
  int Arr_Period[ts->size];
  for (int i = 0; i < ts->size; i++)
  {
    Arr_Period[i] = ts->tasks[i].p;
  }
  return findlcm(Arr_Period,ts->size);
  
};


/*Deadline, t, and period*/
static unsigned int my_EDF_G(unsigned int d ,unsigned int n, unsigned int p)
{
   double q;
   
  int numeratore = n + p - d;
  if(numeratore < 0){
   numeratore = 0; //This because obv max{0, k} == 0 if k is less than 0. That is the case of (n+p-d) < 0 
  }

  q = (double)(numeratore / p);

  return (int)floor(q);
}


int D_Set_EFT(const struct taskset *ts, unsigned int n, unsigned int *t, unsigned int size)
{
  unsigned int points, i;

int minL_H = (CalcLSTAR(ts)>CalcH(ts))?CalcH(ts):CalcLSTAR(ts);


  int AvoidDouble = 0;
  t[0] = ts->tasks[0].d;
  points = 1;
  for (i = 0; i < ts->size; i++) {
    unsigned int j;

    j = 0;
    while (ts->tasks[i].d * j < minL_H) {
      if (points == size) return points;
       for (int k = 0; k < points; k++)
         {
           if(ts->tasks[i].d + j*ts->tasks[i].p == t[k]){
            AvoidDouble = 1;
           }
         }
         
      if(ts->tasks[i].d + j*ts->tasks[i].p < minL_H && AvoidDouble== 0){

         t[points] = ts->tasks[i].d + j*ts->tasks[i].p;
         points = points + 1;
         }
         j = j + 1;
    AvoidDouble = 0;
    }
   
  } 
  qsort(t, points, sizeof(int), cmpfunc);
  return points;
}





unsigned int check_EDF(const struct taskset *ts, unsigned int n)
{
  if(CalcU(ts) > 1){
   printf("U greater than 1! \n");
    return 0;
  }

  unsigned int sp[128];
  int n_sp, i;
  int GL = 0;
  n_sp = D_Set_EFT(ts, n, sp, 128);

  for (i = 0; i < n_sp; i++) {
   for (int j = 0; j < ts->size; j++)
   {
    GL += (my_EDF_G(ts->tasks[j].d, sp[i], ts->tasks[j].p) * ts->tasks[j].c);  
    }
    printf("EDF: dbf(%d) = %d -> ",sp[i], GL);
    if(GL < sp[i])
      printf("OK\n");
    else
      printf("NO\n");
    
 
   if (GL > sp[i]) return 0;
   GL = 0;
  }
  
  return 1;
}

// Analysis under RM //
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

static unsigned int my_ceil(unsigned int n, unsigned int d)
{
  unsigned int q;

  q = n / d;
  if (q * d == n) return q;
  return q + 1;
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


unsigned int check(const struct taskset *ts)
{
  return check_n(ts, ts->size - 1);
}


