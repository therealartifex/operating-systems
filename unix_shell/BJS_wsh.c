/*
Brian Scott
COSC 3053-01
Assignment 3 - "Simple UNIX Shell" 

07 Feb 2016
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#define M_LIN 128

int main(void)
{
    char buf[M_LIN]; // complete command goes here
    int run = 1;

    // loop till we kill it
    while (run) {
        int i;
        int argc = 0;
        int bg = 0;
        char *args[M_LIN/2 + 1] = {NULL}; // args go here

        printf("wsh> "); // wsh = weird shell
        fflush(stdout);

        fgets(buf, M_LIN, stdin); // read the command
        int len = strlen(buf); // get the effective length of the command
        buf[len-1] = '\0'; // sanitize newline
        len = strlen(buf);

        if (buf[len-1] == '&') {
            bg = 1;
            buf[len-2] = '\0';
            len = strlen(buf); // new effective length
        }


        char *token = strtok(buf, " "); // you can't flim-flam the zim-zam!
        while (token && argc < M_LIN/2+1) {
            args[argc++] = token;
            token = strtok(NULL, " ");
        }
        
        // this is the part where it actually does stuff



        // TODO: find out why the backgrounding causes the shell not to print after running a command
        pid_t pid = fork();
        if (pid < 0) {
            // an error has occurred
            fprintf(stderr, "Fork failed for a reason unbeknownst to me\n");
            return 1;
        } else if (pid == 0) {
            // child process
            execvp(args[0], args);
        } else {
            // parent process
            if (bg==1) {
                printf("PARENT: BACKGROUNDING CHILD\n\n");
            } else if (bg==0) {
                printf("PARENT: NO BG\n\n");
                wait(NULL);
            }
        }
    }

    return 0;
}
