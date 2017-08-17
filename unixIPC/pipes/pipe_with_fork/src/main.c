// Reference:
// http://beej.us/guide/bgnet/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char ** argv)
{
  int pipeFds[2];
  int buffer[30];

  pipe(pipeFds);

  if (!fork())
  {
    printf(" CHILD: writing into the pipe\n");
    write(pipeFds[1], "test", 5);
    printf(" CHILD: exiting\n");
    exit(0);
  }
  else
  {
    printf("PARENT: reading from pipe\n");
    read(pipeFds[0], buffer, 5);
    printf("PARENT: read - %s -\n", buffer);
    wait(NULL);
  }

  return 0;
}
