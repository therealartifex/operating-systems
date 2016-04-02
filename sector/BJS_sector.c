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



   return 0;
}

