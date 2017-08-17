// Reference:
// http://beej.us/guide/bgnet/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

volatile sig_atomic_t got_usr1;

void sigusr1_handler(int sig)
{
  got_usr1 = 1;
}

int main(int argc, char ** argv)
{
  struct sigaction signalAction;

  got_usr1 = 0;

  signalAction.sa_handler = sigusr1_handler;
  signalAction.sa_flags = 0;
  sigemptyset(&signalAction.sa_mask);

  if (sigaction(SIGUSR1, &signalAction, NULL) == -1)
  {
    perror("sigaction");
    sleep(1);
  }

  while (!got_usr1)
  {
    printf("PID %d: working hard... \n", getpid());
    sleep(1);
  }

  printf("Done in by SIGUSR1!\n");

  return 0;
}
