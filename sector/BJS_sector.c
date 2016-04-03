/* Brian Scott
* COSC 3603-01
* 01 Apr 2016
* Disk scheduling algorithms
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <string.h>

#define ptc pthread_create
#define ptj pthread_join

static int fcfs_total, sstf_total, scan_total, cscan_total, look_total, clook_total;

void *fcfs(void *p) {

}

void *sstf(void *p) {

}

void *scan(void *p) {

}

void *cscan(void *p) {

}

void *look(void *p) {

}

void *clook(void *p) {

}

int main() {
   int i, j, sectors[1001];
   pthread_t t1, t2, t3, t4, t5, t6;
   
   while(scanf("%d", &i) == 1) {
      sectors[j] = i;
      j++;
   }

   if (ptc(&t1, NULL, fcfs, (void*) sectors)
   | ptc(&t2, NULL, sstf, (void*) sectors)
   | ptc(&t3, NULL, scan, (void*) sectors)
   | ptc(&t4, NULL, cscan, (void*) sectors)
   | ptc(&t5, NULL, look, (void*) sectors)
   | ptc(&t6, NULL, clook, (void*) sectors)) {
      fprintf(stderr,"Thread creation error\n");
      exit(EXIT_FAILURE);
   }
   
   ptj(t1, NULL);
   ptj(t2, NULL);
   ptj(t3, NULL);
   ptj(t4, NULL);
   ptj(t5, NULL);
   ptj(t6, NULL);

   printf("Total head movement for each disk scheduling algorithm:\n
         FCFS:\t%d\n
         SSTF:\t%d\n
         SCAN:\t%d\n
         C-SCAN\t%d\n
         LOOK:\t%d\n
         C-LOOK:\t%d\n");

   return 0;
}

