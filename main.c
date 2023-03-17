#include <stdlib.h>
#include <stdio.h>
#include "lib/cli/cli.h"
#include "string.h"

int main(int argc, char *argv[])
{

  if (strcmp(argv[1], "--visualizacao") == 0 && argc == 5)
  {
    visualization(argv[2], argv[3], argv[4]);
  }
  else
  {
    printf("Parâmetros não reconhecidos. Verifique se a quantidade fornecida foi correta ou se um input realmente existe no diretório inputs.");
  }

  return 0;
}