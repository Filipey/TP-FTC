#include <stdlib.h>
#include <stdio.h>
#include "lib/io/io.h"

int main()
{
  Afd *afd = mallocAfdFromFile("inputs/afd.txt");
  exportAfdTxt(afd, "teste-impar-par.txt");
  freeMemory(afd);
  return 0;
}