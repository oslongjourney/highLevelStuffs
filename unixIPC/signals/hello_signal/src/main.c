#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define reply "Hummm!!!\n"

void sigint_handler (int sig)
{
  write (0, reply, sizeof(reply));
}

int main(int argc, char ** argv)
{
  char buffer[200];
  struct sigaction sigAction;

  sigAction.sa_handler = sigint_handler;
  sigAction.sa_flags = SA_RESTART;
  sigemptyset(&sigAction.sa_mask);

  if (sigaction(SIGINT, &sigAction, NULL) == -1)
  {
    perror("Sigaction");
    exit(1);
  }

  printf("Enter a string:\n");

  if (fgets(buffer, sizeof(buffer), stdin) == NULL)
  {
    perror ("fgets");
  }
  else
  {
    printf ("You entered: %s\n", buffer);
  }

  return 0;
}
