#include "stdlib.h"
#include "stdio.h"
#include "cli.h"
#include "../afd/afd.h"
#include "../io/io.h"
#include "string.h"

void visualization(char *inputFilename, char *outputFileExtension, char *outputFilename)
{
  Afd *afd = mallocAfdFromFile(inputFilename);

  printf("INPUT FILENAME: %s", inputFilename);
  printf("OUTPUT FILE EXTENSION: %s", outputFileExtension);
  printf("OUTPUT FILENAME: %s", outputFilename);

  if (strcmp(outputFileExtension, ".dot") == 0)
  {
    exportAfdDot(outputFilename, afd);
    freeMemory(afd);
  }
  else if (strcmp(outputFilename, ".txt") == 0)
  {
    exportAfdTxt(outputFilename, afd);
    freeMemory(afd);
  }
  else
  {
    printf("Erro ao ler o gerar arquivo: %s%s", outputFilename, outputFileExtension);
    exit(1);
  }
}