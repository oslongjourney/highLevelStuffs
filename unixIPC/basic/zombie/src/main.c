// Reference:
// http://www.unix.com/unix-for-dummies-questions-and-answers/100737-how-do-you-create-zombie-process.html

#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main ()
{
  pid_t child_pid;

  child_pid = fork ();

  if (child_pid > 0)
  {
    sleep (60);
  }
  else
  {
    exit (0);
  }
  return 0;
}
