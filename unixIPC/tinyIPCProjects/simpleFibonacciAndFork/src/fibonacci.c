#include "fibonacci.h"

int fibonacci(unsigned int pPosition)
{
  if (!pPosition)
  {
    return 0;
  }
  if (pPosition == 1)
  {
    return 1;
  }

  return (fibonacci(pPosition -1) + fibonacci(pPosition - 2));
}
