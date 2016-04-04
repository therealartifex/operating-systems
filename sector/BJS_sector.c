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
   int *s = p;
   int i;

   for (i=1;i<=1001;i++) fcfs_total += abs( *(s+i) - *(s+(i-1)) );
}

void *sstf(void *p) {
   int *s = p;
   int init = *s;
   int index, i, currentDist, minDist=abs(init - *(s+1));

   // Enclose this loop in another for loop that will add up the total head movement
   // Also find a way to remove sectors that have already been processed
   for (i=2; i<=1001;i++) {
      currentDist = abs(init - *(s+i));
      if (currentDist < minDist) {
         index = i;
         minDist = currentDist;
      }
   }

   
   sstf_total;
}

void *scan(void *p) {

}

void *cscan(void *p) {

}

void *look(void *p) {

}

void *clook(void *p) {

}

int getClosest(int init, int arr[]) {
   int index, i, currentDist, minDist=abs(init-arr[0]);

   for (i=1; i<=10;i++) {
      currentDist = abs(init-arr[i]);
      if (currentDist < minDist) {
         index = i;
         minDist = currentDist;
      }
   }

   return arr[index];
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

   printf("Total head movement for each disk scheduling algorithm:\nFCFS\t%d\nSSTF\t%d\nSCAN\t%d\nC-SCAN\t%d\nLOOK\t%d\nC-LOOK\t%d\n",fcfs_total, sstf_total, scan_total, cscan_total, look_total, clook_total);

   return 0;
}

