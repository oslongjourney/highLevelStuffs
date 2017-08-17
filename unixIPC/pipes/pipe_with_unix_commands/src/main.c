// Reference:
// http://beej.us/guide/bgnet/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char ** argv)
{
  int pipeFds[2];

  pipe(pipeFds);

  if (!fork())
  {
    close(1);
    dup(pipeFds[1]);
    close(pipeFds[0]);
    execlp("ls", "ls", NULL);
  }
  else
  {
    close(0);
    dup(pipeFds[0]);
    close(pipeFds[1]);
    execlp("wc", "wc", "-l", NULL);
  }

  return 0;
}
