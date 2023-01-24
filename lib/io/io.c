#include <stdlib.h>
#include <stdio.h>
#include "io.h"

void generateAfdFromFile(char *filename)
{
  FILE *file = fopen(filename, "rt");
  char *line;
  char buffer[100];
  int lineCount = 0;
  StateSet *states = NULL;
  StateSet *finalStates = NULL;
  TransitionSet *transitions = NULL;

  if (!file)
  {
    printf("Erro ao ler o arquivo!\n");
    return;
  }

  while (!feof(file))
  {
    line = fgets(buffer, 100, file);
    if (lineCount == 0)
    {
      states = initializeStateSet((long)line); // Converting char to long
    }
    lineCount++;
  }

  fclose(file);
}