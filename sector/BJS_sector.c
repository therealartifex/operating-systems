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

static int sectors[1001];

void *fcfs(void *p) {

}

int main() {
   int i;
   char buf[1024];
   
   while (1) {
      sectors[i] = atoi(buf);
      i++;
   }
   
   return 0;
}

