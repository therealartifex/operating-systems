/* Brian Scott
 * COSC 3053-10
 * 18 Feb 2016
 * Multithreaded statistics program
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>

// global variables
static double min, max, avg;
static int arg_size;

// simple average calculation
void *average(void* p)
{
	double *f = p;
	double sum = 0.0;
	
	int i;
	for (i=0;i<arg_size;i++) sum += *(f+i);
	
	avg = sum/arg_size;
	
}

// simple maximum calculation
void *maximum(void* p)
{
	double *f = p;
	double t = INT_MIN;
	
	int i;
	for (i=0;i<arg_size;i++) if (*(f+i) > t) t = *(f+i);
	
	max = t;
}

// simple minimum calculation
void *minimum(void* p)
{
	double *f = p;
	double t = INT_MAX;
	
	int i;
	for (i=0;i<arg_size;i++) if (*(f+i) < t) t = *(f+i);
	
	min = t;
}

// entry point
int main(int argc, char *argv[])
{
     pthread_t t1, t2, t3; // threads
     arg_size = argc-1; // number of args not including name
     
     int i;
     double fl_args[arg_size];
     for (i = 0; i<arg_size; i++){
		 fl_args[i]=atof(argv[i+1]); // convert to floating-point numbers
	 }
 
	 // create independent threads each of which will execute a function	 
     if(pthread_create(&t1, NULL, minimum, (void*) fl_args))
     {
         fprintf(stderr,"Error\n");
         exit(EXIT_FAILURE);
     }
 
     if(pthread_create(&t2, NULL, maximum, (void*) fl_args))
     {
         fprintf(stderr,"Error\n");
         exit(EXIT_FAILURE);
     }
     
     if(pthread_create(&t3, NULL, average, (void*) fl_args))
     {
         fprintf(stderr,"Error\n");
         exit(EXIT_FAILURE);
     }
 
      
     // wait until threads are complete before main continues
     pthread_join(t1, NULL);
     pthread_join(t2, NULL);
	 pthread_join(t3, NULL);
	 
	 printf("Average:\t%.3f\nMinimum:\t%.3f\nMaximum:\t%.3f\n", avg, min, max); 
	 
     return 0;
}
 

