#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char ** argv)
{
  pid_t pid;
  int returnValue = 0;

  pid = fork();

  switch (pid)
  {
    case -1:
      perror("fork");
      exit(1);
      break;
    case 0:
      printf("\tCHILD: We are inside child process!\n");
      printf("\tCHILD DATA:\n");
      printf("\t\tPID: %d\n", getpid());
      printf("\t\tParent PID: %d\n", getppid());
      printf("Just for fun, type a small number:\n");
      scanf(" %d", &returnValue);
      break;
    default:
      printf("\tPARENT: I am the parent process\n");
      printf("\tPARENT DATA:\n");
      printf("\t\tPID: %d\n", getpid());
      printf("\t\tMY CHILD: %d\n", pid);
      printf("=> Waiting for my child...\n");
      wait(&returnValue);
      printf("PARENT: Child exit status: %d\n", WEXITSTATUS(returnValue));
      printf("PARENT: Child said: %d\n", returnValue);
      printf("PARENT: bye\n");
      break;
  }

  return 0;
}
