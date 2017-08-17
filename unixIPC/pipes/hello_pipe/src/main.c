// Reference:
// http://beej.us/guide/bgnet/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char ** argv)
{
  int pipeFds[2];
  char buffer[30];

  if (pipe(pipeFds) == -1)
  {
    perror ("pipe");
    exit (1);
  }

  printf("Writing to file descritor #%d\n", pipeFds[1]);
  write(pipeFds[1], "test", 5);

  printf("Reading from file descriptor #%d\n", pipeFds[0]);
  read(pipeFds[0], buffer, 5);
  printf("read \"%s\"\n", buffer);

  return 0;
}
