/* Basic include statements */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h> // for timing
#include <math.h>       

#define MAXTHREADS 100

/* global integer variables NTHREADS, TOTAL  */
int NTHREADS=4;
int TOTAL;

/* global integer array RES[] */
int RES[MAXTHREADS];
pthread_t THREADS_ID[MAXTHREADS];

/* constant N */
int N=10000000;

/* global variable V as a pointer to int */
int *V;



/* Time function */
double now(){
   struct timeval t; double f_t;
   gettimeofday(&t, NULL); 
   f_t = t.tv_usec; f_t = f_t/1000000.0; f_t +=t.tv_sec;
   return f_t; 
}



/* Exercise 1 */
/* function int even(int *V, int n) */
int even(int *V, int n)
{
int number=0;
int i;
for(i=0;i<n;i++)
{
if (V[i]%2==0) number=number+1;
else number=number;
}
return number;
}


/* Exercise 2 */
/* initialize the array V with random integer values (use the function rand()) */

void init(int *V,int n)
{
int i;
// V[n];
for(i=0;i<n;i++) V[i]=rand();
// return V;
}


/* Exercise 3 

int main()
{
V=malloc(N*sizeof(int));
init(V,N);
TOTAL=even(V,N);
printf("The total number of even values in V is : %d\n",TOTAL);

free(V);
}

*/


/* Exercise 4 */
/* function thread_even(void *thread_id) */

void *thread_even(void *thread_id){
int number=0;
int id,i;
id =(int)(thread_id);

for(i=id*(N/NTHREADS);i<(id+1)*(N/NTHREADS);i++) 
{
if (V[i]%2==0) number=number+1; 
//else number=number;
}
RES[id]=number;
pthread_exit(NULL);
}


/* Exercise 5 */
/* The multi-threaded version of even(int *V, int n) with NTHREADS. */

int parallel_even(int *V, int n){

int number=0;
int i;

for(i=0;i<NTHREADS;i++) pthread_create(&THREADS_ID[i],NULL,thread_even,(void *)i);

for(i=0;i<NTHREADS;i++) pthread_join(THREADS_ID[i],NULL);

for(i=0;i<NTHREADS;i++) number=number+RES[i];

return number;

}


/* Exercise 6 */
/* Completion of main function */

int main()
{
V=malloc(N*sizeof(int));
init(V,N);
int TOTAL_Seq,TOTAL_Par;
double t0,t1,t2,t3 ;


t0=now();TOTAL_Seq=even(V,N); t1=now(); 
TOTAL_Par = parallel_even(V,N);t2=now();
printf("For Single thread /Sequential we have %d even numbers. Time : %6.4f\n",TOTAL_Seq,t1-t0); 
printf("For Multi thread /Parallel we have %d even numbers. Time : %6.4f\n",TOTAL_Par,t2-t1);
printf("For %d threads the SpeedUp is %6.4f\n",NTHREADS,(t1-t0)/(t2-t1));
free(V);

}

