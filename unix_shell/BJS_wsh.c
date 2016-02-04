/*
Brian Scott
COSC 3053-01
Assignment 3 - "Simple UNIX Shell" 

03 Feb 2016
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define M_LIN 256

int main(void)
{
	char *args[M_LIN/2 + 1]; // args go here
	char buf[M_LIN]; // complete command goes here
	int run = 1;
	
	// loop till we kill it
	while (run) {
		int i;
		int argc = -1;
      int bg = 0;
		
		printf("wsh> "); // wsh = weird shell
		fflush(stdout);
		
		fgets(buf, M_LIN, stdin); // read the command
				
		for(i=0;i<sizeof(buf);i++) {
			if (buf[i] == '&') bg = 1;
			if(isspace(buf[i])){
				 buf[i] = '\0';
				 if (!i==sizeof(buf)-1) args[++argc]=&buf[i+1];
			}      
		}
	}

	return 0;
}
