#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/shm.h>

#include "fibonacci.h"

#define MAX_SEQUENCE 10

typedef struct
{
  long fib_sequence[MAX_SEQUENCE];
  int sequence_size;
} shared_data;

int main(int argc, char ** argv)
{
  pid_t childProcess;

  // Validate parameters
  if (argc != 2)
  {
    printf("Invalid number of arguments\n");
    printf("binary <fibonnaciValue>\n");
    exit(1);
  }

  int targetFibonnaci = atoi(argv[1]);
  if (targetFibonnaci > MAX_SEQUENCE)
  {
    printf("Sadly we cannot support %d number\n", targetFibonnaci);
    printf("Try to recompile with a larger number of MAX_SEQUENCE\n");
    exit(1);
  }
  else if (targetFibonnaci < 2)
  {
    printf("Provide an integer number greater than 1\n");
    exit(1);
  }

  // Shared memory
  shared_data * pointerToSharedData = 0;
  key_t key = ftok("./", 'I');

  if (key < 0)
  {
    perror("ftok");
    exit(1);
  }

  int sharedMemoryID = shmget(key, sizeof(shared_data), 0644 | IPC_CREAT);
  if (sharedMemoryID < 0)
  {
    perror("shmget");
    exit(1);
  }

  pointerToSharedData = (shared_data *)shmat(sharedMemoryID, (void *)0, 0);
  if ((char *)(pointerToSharedData) == (char *)(-1))
  {
    perror("shmat");
    shmctl(sharedMemoryID, IPC_RMID, NULL);
    exit(1);
  }

  pointerToSharedData->sequence_size = targetFibonnaci;

  // Child and parent
  childProcess = fork();
  if (childProcess < 0)
  {
    perror("fork");
    exit(1);
  }

  // Child
  if (!childProcess)
  {
    for (int i = 0, f = 1; f <= pointerToSharedData->sequence_size; i++, f++)
    {
      pointerToSharedData->fib_sequence[i] = fibonacci(f);
    }
    exit(0);
  }
  // Parent
  else
  {
    wait(NULL);
    for (int i = 0; i <= pointerToSharedData->sequence_size; i++)
    {
      printf ("%ld ", pointerToSharedData->fib_sequence[i]);
    }
    printf("\n");
  }

  // Clean up stuffs
  printf("Parent processes clean up and say Bye Bye!\n");
  int status = shmdt((void *)pointerToSharedData);
  if (status < 0)
  {
    perror("shmdt");
    exit(1);
  }

  status = shmctl(sharedMemoryID, IPC_RMID, NULL);
  if (status < 0)
  {
    perror("shmctl");
    exit(1);
  }

  return 0;
}
