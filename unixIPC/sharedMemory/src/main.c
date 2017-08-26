#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>

int main(int argc, char ** argv)
{
  if (argc != 2)
  {
    printf("Invalid number of arguments\n");
    exit (1);
  }

  int key = atoi(argv[1]);
  struct shmid_ds buffstat;

  int rc = shmctl(key, IPC_STAT, &buffstat);
  if (rc < 0)
  {
    perror("shmctl");
    exit(1);
  }

  printf("Segment ID: %d\n", key);
  printf("Mode: 0x%0x\n", buffstat.shm_perm);
  printf("Owner UID: %d\n", buffstat.shm_cpid);
  printf("Size: %d\n", buffstat.shm_segsz);
  printf("Number of attached: %d\n", buffstat.shm_nattch);

  return 0;
}
