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
#include <sys/types.h>

#define M_LIN 128

int main(void)
{
   char *args[M_LIN/2 + 1] = {NULL}; // args go here
	char buf[M_LIN]; // complete command goes here
	int run = 1;
	
	// loop till we kill it
	while (run) {
		int i;
		int arg_next = 0;
      int bg = 0;
		
		printf("wsh> "); // wsh = weird shell
		fflush(stdout);
		
		fgets(buf, M_LIN, stdin); // read the command
      int len = strlen(buf); // get the effective length of the command

		args[0] = &buf[0];

		for(i=0;i<len;i++) {
			if (buf[i] == '&') bg = 1;
			if(isspace(buf[i])){
				 buf[i] = '\0';
				 if (!(i==len-1)) args[++arg_next]=&buf[i+1]; // when we hit whitespace, set the next pointer in args to the next char in buf
			}
		}

      int argc = sizeof(args)/sizeof(char*);

      int j;
      for(j=0;j<argc;j++){
         printf("%d : %s\n",j,args[j]);
      }


      // this is the part where it actually does stuff    
      
      pid_t pid = fork();
      if (pid < 0) {
         // an error has occurred
         fprintf(stderr, "Fork failed\n");
         return 1;
      } else if (pid == 0) {
         execvp(args[0], args);
      } else {
         if (bg==0) wait(NULL);
      }
	}

	return 0;
}
