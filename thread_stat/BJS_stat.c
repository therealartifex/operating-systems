#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

static float min, max, avg;

void *average(void* p)
{}

void *maximum(void* p)
{}

void *minimum(void* p)
{}
	
int main(int argc, char *argv[])
{
     pthread_t thread1, thread2, thread3;
     int iret1, iret2, iret3, i;
     
     float fl_args[argc-1];
     for (i = 0; i<argc; i++){
		 fl_args[i]=atof(argv[i+1]);
	 }
 
    /* Create independent threads each of which will execute function */
 
     iret1 = pthread_create( &thread1, NULL, minimum, (void*) fl_args);
     if(iret1)
     {
         fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
         exit(EXIT_FAILURE);
     }
 
     iret2 = pthread_create( &thread2, NULL, maximum, (void*) fl_args);
     if(iret2)
     {
         fprintf(stderr,"Error - pthread_create() return code: %d\n",iret2);
         exit(EXIT_FAILURE);
     }
     
     iret3 = pthread_create( &thread3, NULL, average, (void*) fl_args);
     if(iret3)
     {
         fprintf(stderr,"Error - pthread_create() return code: %d\n",iret3);
         exit(EXIT_FAILURE);
     }
 
      
     /* Wait till threads are complete before main continues. Unless we  */
     /* wait we run the risk of executing an exit which will terminate   */
     /* the process and all threads before the threads have completed.   */
 
     pthread_join(thread1, NULL);
     pthread_join(thread2, NULL);
	 pthread_join(thread3, NULL);
	 
     return 0;
}
 

