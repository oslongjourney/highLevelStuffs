// Reference:                                                                      
// http://beej.us/guide/bgnet/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define FIFO_NAME "speak_and_tick"

int main(int argc, char ** argv)
{
  char buffer[300];
  int num = 0, fd = 0;

  mknod(FIFO_NAME, S_IFIFO | 0666, 0);

  printf("Waiting for writers...\n");
  fd = open(FIFO_NAME, O_RDONLY);
  printf("Got a writer\n");

  do
  {
    if ((num = read(fd, buffer, 300)) == -1)
      perror("read");
    else
    {
      buffer[num] = '\0';
      printf("tick: read %d bytes: %s\n", num, buffer);
    }
  } while (num > 0);

  return 0;
}
