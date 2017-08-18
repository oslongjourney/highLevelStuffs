#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/wait.h>

#include "fibonacci.h"

int main(int argc, char ** argv)
{
  pid_t childProcess;

  if (argc != 2)
  {
    printf("Invalid number of arguments\n");
    printf("binary <fibonnaciValue>\n");
    exit(1);
  }

  int targetFibonnaci = atoi(argv[1]);

  childProcess = fork();
  if (childProcess < 0)
  {
    perror("fork");
    exit(1);
  }

  // Child
  if (!childProcess)
  {
    for (int i = 1; i <= targetFibonnaci; i++)
    {
      printf(" %d ", fibonacci(i));
    }
    printf ("\n");
    exit(0);
  }
  // Parent
  else
  {
    wait(NULL);
    printf("Parent process say: bye bye\n");
  }

  return 0;
}
