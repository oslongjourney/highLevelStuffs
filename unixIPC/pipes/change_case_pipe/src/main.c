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

#define WRITE 1
#define READ 0

void invertCase(char * pTarget)
{
  if (!pTarget)
  {
    return;
  }
  for (; *pTarget; pTarget++)
  {
    *pTarget = (isupper(*pTarget)) ? tolower(*pTarget) : toupper(*pTarget);
  }
}

int main (int argc, char ** argv)
{
  if (argc != 2)
  {
    printf("Wrong number of arguments\n");
    printf("please use: ./binary 'String'\n");
    exit(1);
  }

  int pipeFds1[2];
  int pipeFds2[2];
  char * buffer = 0;
  int inputSize = 0;

  if (pipe(pipeFds1) < 0 || pipe(pipeFds2) < 0)
  {
    perror("pipe");
    exit(1);
  }

  inputSize = strlen(argv[1]);

  // Start the work!
  if (!fork())
  {
    // Close unnecessary file descriptors
    close(pipeFds1[WRITE]); // Pipe 1 is used just for read in the child
    close(pipeFds2[READ]); // Pipe 2 is used just for write to the parent

    // Allocate space
    if (!(buffer = malloc(sizeof(char) * inputSize)))
    {
      perror("malloc");
      exit(1);
    }

    read(pipeFds1[READ], buffer, inputSize);
    printf("Received (Child): %s\n", buffer);

    invertCase(buffer);

    write(pipeFds2[WRITE], buffer, inputSize);

    free(buffer);

    exit(0);
  }
  else
  {
    // Close
    close(pipeFds1[READ]);
    close(pipeFds2[WRITE]);

    write(pipeFds1[WRITE], argv[1], inputSize);

    if (!(buffer = malloc(sizeof(char) * inputSize)))
    {
      perror("malloc");
      exit(1);
    }

    read(pipeFds2[READ], buffer, inputSize);
    wait(NULL);
    printf("The new string (Parent): %s\n", buffer);
    free(buffer);
  }
  return 0;
}
