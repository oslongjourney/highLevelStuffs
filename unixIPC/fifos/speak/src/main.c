// Reference:
// http://beej.us/guide/bgnet/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_NAME "speak_and_tick"

int main(int argc, char ** argv)
{
  char buffer[300];
  int num = 0, fd = 0;

  mknod(FIFO_NAME, S_IFIFO | 0666, 0);

  printf("Waiting for readers...\n");
  fd = open(FIFO_NAME, O_WRONLY);

  printf("Got a reader -- type some stuff\n");

  while (fgets(buffer, sizeof(buffer), stdin), !feof(stdin))
  {
    if ((num = write(fd, buffer, strlen(buffer))) == -1)
    {
      perror("write");
    }
    else
    {
      printf("speak: wrote %d byte\n", num);
    }
  }

  return 0;
}
