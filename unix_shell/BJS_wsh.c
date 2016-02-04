/*
Brian Scott
COSC 3053-01
Assignment 3 - "Simple UNIX Shell" 

03 Feb 2016
*/

#include <stdio.h>
#include <unistd.h>

#define M_LIN 80

int main(void)
{
	char *args[M_LIN/2 + 1];
	int run = 1;
	
	while (run) {
		printf("wsh>");
		fflush(stdout);
		
		
	}
	return 0;
}
