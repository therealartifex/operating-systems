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
		int argc;
		
		printf("wsh> "); // wsh = weird shell
		fflush(stdout);
		
		fgets(buf, M_LIN, stdin); // read the command
		
		args[0]=&buf[0]; // first command is first argument
		
		for(i=0;i<strlen(buf);i++) {
			if(isspace(buf[i])){
				 buf[i] = '\0';
				 args[++argc]=&buf[i+1];
			}
		}
			
		printf("%s\n",buf);
	}
	return 0;
}
