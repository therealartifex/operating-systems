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

#define NTHREADS 5
#define LEFT (i+NTHREADS-1)%NTHREADS
#define RIGHT (i+1)%NTHREADS
#define TK 1 // thinking
#define HG 2 // hungry
#define ET 3 // eating
#define lock pthread_mutex_lock
#define unlock pthread_mutex_unlock

pthread_cond_t CV[NTHREADS];
pthread_mutex_t M, output_lock; // the output_lock mutex circumvents annoying stdout interleaving
int state[NTHREADS]; // state array

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

	for (i = 0; i < NTHREADS; i++) {
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

// PHILOSOPHRES CODE FILE BELOW

int nsteps, maxsteps = 0;  /* number of steps to run this test */
int eat_count[NTHREADS];          /* number of steps for each thread */

/* The subprogram trace is for testing and debugging.
*    It allows us to see what is happening,
*       and to shut down the philosophers when the program has
*          run long enough for us to see that it seems to be working
*           */

void trace(int i, char *s) {
/* print out message, for use in execution tracing
*      i = philospher ID
*           s = message
*              */
lock(&outlock);
if (strcmp (s, "eating") == 0) eat_count [i]++;
/*
*   fprintf(stdout,"%d: %s\n",i,s);
*    */
if (nsteps++ > maxsteps) {
/* don't exit while we are holding any chopsticks */
if (strcmp(s,"thinking") == 0) {
unlock(&outlock);
/*
*       fprintf (stderr, "thread done\n");
*        */
pthread_exit(0);
}
}
unlock(&outlock);
}

void * philosopher_body(void *arg) {
int self = *(int *) arg;
for (;;) {
trace(self,"thinking");
chopsticks_take(self);
trace(self,"eating");
chopsticks_put(self);
}
}

int main() {
int i;
pthread_t th[NTHREADS]; /* IDs of the philospher threads */
int       no[NTHREADS]; /* corresponding table position numbers*/
pthread_attr_t attr;

for (i = 0; i < NTHREADS; i++) eat_count [i] = 0;

pthread_mutex_init(&outlock, NULL);

/* initialize the object chopsticks */
chopsticks_init();

fprintf(stdout,"enter number of steps to run: "); fflush(stdout);
fscanf(stdin,"%d",&maxsteps);

pthread_attr_init (&attr); /* sets default attributes */

pthread_setconcurrency (4);
/* suggest four kernel threads for this process */

pthread_attr_setscope (&attr, PTHREAD_SCOPE_SYSTEM);
/* set system-wide contention scope */

/* start up the philosopher threads */
for (i = 0; i < NTHREADS; i++) {
no[i] = i;
pthread_create(&th[i], NULL, philosopher_body, (int *) &no[i]);
}

/* wait for all the threads to shut down */
for (i = 0; i < NTHREADS; i++) pthread_join(th[i], NULL);

for (i = 0; i < NTHREADS; i++) {
fprintf (stderr, "philospher %d ate %d times\n", i, eat_count [i]);
}

return 0;
}
