/*
 Copyright (C) 2017 Rodrigo Siqueira  <siqueira@kuniri.org>

 This source code is licensed under the GNU general public license,
 Version 3.  See the file COPYING for more details
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

#define WRITE 1
#define READ 0

int main (int argc, char ** argv)
{
  if (argc != 3)
  {
    printf("Wrong number of arguments\n");
    printf("please use: ./binary file1.txt file2.txt\n");
    exit(1);
  }

  int pipeFds1[2];
  int inputSize = 0;

  struct stat fileStat;
  char * buffer = 0;
  int bufferSize = 0;

  if (pipe(pipeFds1) < 0)
  {
    perror("pipe");
    exit(1);
  }

  stat(argv[1], &fileStat);
  bufferSize = sizeof(char) * fileStat.st_size;

  // Start the work!
  if (!fork())
  {
    // Close unnecessary file descriptors
    close(pipeFds1[WRITE]);

    // Allocate space
    if (!(buffer = malloc(bufferSize)))
    {
      perror("malloc");
      exit(1);
    }

    read(pipeFds1[READ], buffer, bufferSize);

    FILE * dest =  fopen(argv[2], "w");
    if (!dest)
    {
      perror("fopen");
      exit(1);
    }
    fwrite(buffer, sizeof(char), fileStat.st_size, dest);

    free(buffer);
    close(pipeFds1[READ]);
    fclose(dest);

    exit(0);
  }
  else
  {
    // Close
    close(pipeFds1[READ]);

    // Open file
    FILE * origin =  fopen(argv[1], "r");
    if (!origin)
    {
      perror("fopen");
      exit(1);
    }

    buffer = malloc(bufferSize);
    if (!buffer)
    {
      exit(1);
    }

    fread(buffer, sizeof(char), fileStat.st_size, origin);
    write(pipeFds1[WRITE], buffer, bufferSize);
    wait(NULL);

    free(buffer);
    close(pipeFds1[READ]);
    fclose(origin);
  }
  return 0;
}
