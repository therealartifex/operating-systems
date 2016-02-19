#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>

static double min, max, avg;
static int arg_size;

void *average(void* p)
{
	double *f = p;
	double sum = 0.0;
	
	int i;
	for (i=0;i<arg_size;i++){
		printf("%d : %f\n", i, *(f+i));
		sum += *(f+i);
	}
	
	avg = sum/arg_size;
	// printf("Average:\t%.3f\n", sum/arg_size);
	
}

void *maximum(void* p)
{
	double *f = p;
	double t = INT_MIN;
	
	int i;
	for (i=0;i<arg_size;i++) if (*(f+i) > t) t = *(f+i);
	
	max = t;
}

void *minimum(void* p)
{
	double *f = p;
	double t = INT_MAX;
	
	int i;
	for (i=0;i<arg_size;i++) if (*(f+i) < t) t = *(f+i);
	
	min = t;
}
	
int main(int argc, char *argv[])
{
     pthread_t thread1, thread2, thread3;
     arg_size = argc-1;
     
     int i;
     double fl_args[arg_size];
     for (i = 0; i<arg_size; i++){
		 fl_args[i]=atof(argv[i+1]);
		 //printf("%d : %f\n", i, fl_args[i]);
	 }
 
	 // Create independent threads each of which will execute a function	 
     if(pthread_create( &thread1, NULL, minimum, (void*) fl_args))
     {
         fprintf(stderr,"Error\n");
         exit(EXIT_FAILURE);
     }
 
     if(pthread_create( &thread2, NULL, maximum, (void*) fl_args))
     {
         fprintf(stderr,"Error\n");
         exit(EXIT_FAILURE);
     }
     
     if(pthread_create( &thread3, NULL, average, (void*) fl_args))
     {
         fprintf(stderr,"Error\n");
         exit(EXIT_FAILURE);
     }
 
      
     // Wait till threads are complete before main continues. Unless we 
     // wait we run the risk of executing an exit which will terminate  
     // the process and all threads before the threads have completed.  
 
     pthread_join(thread1, NULL);
     pthread_join(thread2, NULL);
	 pthread_join(thread3, NULL);
	 
	 printf("Average:\t%.3f\nMinimum:\t%.3f\nMaximum:\t%.3f\n", avg, min, max); 
	 
     return 0;
}
 

