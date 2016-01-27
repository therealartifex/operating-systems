/*
Brian Scott
COSC 3053-01
"File Copy"
26 Jan 2016
*/

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define BUFFER_SIZE 4096

// entry point
int main(int argc, char* argv[]) {
  
  // declarations for file descriptor, block size, buffer
  int fdesc_in, fdesc_out;
  ssize_t block_in, block_out;
  char buf[BUFFER_SIZE];

  if (argc != 3) {
    printf ("Usage: ./fcopy file1 file2\n");
    return 1;
  }

  printf("File to be copied: %s\nNew filename: %s\n", argv[1], argv[2]);
  
  // open file as read-only
  fdesc_in = open(argv [1], O_RDONLY);
  if (fdesc_in == -1) {
    perror ("problem opening origin file\n");
    return 2;
  }
  
  // create and open destination file
  fdesc_out = open(argv[2], O_WRONLY | O_CREAT, 0644);
  if (fdesc_out == -1) {
    perror("problem opening destination file\n");
    return 3;
  }

  // read data from source and write to destination in blocks of size BUFFER_SIZE
  while ((block_in = read(fdesc_in, &buf, BUFFER_SIZE)) > 0) {
    block_out = write (fdesc_out, &buf, (ssize_t) block_in);
    
    if (block_out != block_in) {
       perror("write error\n");
       return 4;
    }
  }
  
  // close files
  close (fdesc_in);
  close (fdesc_out);

  return 0;
}
