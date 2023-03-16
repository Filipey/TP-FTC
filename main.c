#include <stdlib.h>
#include <stdio.h>
#include "lib/io/io.h"

int main()
{
  Afd *afd = mallocAfdFromFile("inputs/afd.txt");
  exportAfdTxt("teste-impar-par.txt", afd);
  exportAfdDot("teste-impar-par.dot", afd);
  freeMemory(afd);
  return 0;
}