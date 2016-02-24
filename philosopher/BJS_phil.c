/* Brian Scott
* COSC 3053-01
* Modified dining philosophers problem
* 22 Feb 2016
*/

#include <unistd.h>
#include <ctype.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define PH 5
#define LEFT (i+PH-1)%PH
#define RIGHT (i+1)%PH
#define TK 1 // thinking
#define HG 2 // hungry
#define ET 3 // eating
#define lock pthread_mutex_lock
#define unlock pthread_mutex_unlock

pthread_cond_t CV[PH];
pthread_mutex_t M, output_lock; // the output_lock mutex circumvents annoying stdout interleaving
int state[PH]; // state array

int update_state(int i) {
	if (state[i] == HG && state[LEFT] != ET && state[RIGHT] != ET) {
		state[i] = ET;
		pthread_cond_signal(&CV[i]);
	}
	return 0;
}

void chopsticks_init() {
	int i;
	pthread_mutex_init(&M, NULL);

	for (i = 0; i < PH; i++) {
		pthread_cond_init (&CV[i], NULL);
		state[i] = TK;
	}
}

void chopsticks_take(int i) {
	lock(&M);
	state[i] = HG;
	update_state(i);
	while (state[i] == HG) pthread_cond_wait (&CV[i],&M); // loop while hungry
	unlock(&M);
}

void chopsticks_put(int i) {
	lock(&M);
	state[i] = TK;
	update_state (LEFT);
	update_state (RIGHT);
	unlock(&M);
}

int nsteps, maxsteps = 0;  /* number of steps to run this test */
int eat_count[PH];          /* number of steps for each thread */

/* The subprogram trace is for testing and debugging.
*    It allows us to see what is happening,
*       and to shut down the philosophers when the program has
*          run long enough for us to see that it seems to be working
*           */

void trace(int i, char *s) {
   // i = philospher ID
   // s = message
	
   lock(&output_lock);
	if (strcmp (s, "eating") == 0) eat_count [i]++;
   //   fprintf(stdout,"%d: %s\n",i,s);
	
   if (nsteps++ > maxsteps) {
		if (strcmp(s,"thinking") == 0) {
			unlock(&output_lock);
         // fprintf (stderr, "thread done\n");
			pthread_exit(0);
		}
	}
	
   unlock(&output_lock);
}

void * phil_exec(void *arg) {
   int self = *(int *) arg;
   for (;;) {
      trace(self,"thinking");
      chopsticks_take(self);
      trace(self,"eating");
      chopsticks_put(self);
   }
}

int main(int argc, char *argv[]) {
   int i;
   pthread_t tid[PH]; // IDs of the philospher threads
   int no[PH]; // corresponding table position numbers
   pthread_attr_t attr;
   
   if (argc < 2 && atoi(argv[1]) == 0) maxsteps = 4;
   else maxsteps = atoi(argv[1]);

   for (i = 0; i < PH; i++) eat_count[i] = 0;

   pthread_mutex_init(&output_lock, NULL);

   chopsticks_init(); // initialize chopsticks
   pthread_attr_init(&attr); // set default attributes
   pthread_setconcurrency(4); // suggest four kernel threads for this process
   pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM); // set system-wide contention scope

   // start up the philosopher threads
   for (i = 0; i < PH; i++) {
      no[i] = i;
      pthread_create(&tid[i], NULL, phil_exec, (int *) &no[i]);
   }

   // wait for threads to finish
   for (i = 0; i < PH; i++) pthread_join(tid[i], NULL);

   for (i = 0; i < PH; i++) fprintf (stderr, "philospher %d ate %d times\n", i, eat_count [i]);

   return 0;
}
