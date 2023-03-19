#include "stdlib.h"
#include "stdio.h"
#include "cli.h"
#include "../afd/afd.h"
#include "../io/io.h"
#include "string.h"

/**
 * Operação de visualização do AFD em .txt ou .dot
 * @param inputFilename Nome do arquivo de entrada
 * @param outputFileExtension Extensão do arquivo de saída
 * @param outputFilename Nome do arquivo de saída
 */
void visualization(char *inputFilename, char *outputFileExtension, char *outputFilename)
{
  Afd *afd = mallocAfdFromFile(inputFilename);

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

void complement(char *inputFilename, char *outputFileExtension, char *outputFilename)
{
  Afd *afd = mallocAfdFromFile(inputFilename);
  generateComplement(afd);

  if (strcmp(outputFileExtension, ".dot") == 0)
  {
    exportAfdDot(outputFilename, afd);
    freeMemory(afd);
  }
  else if (strcmp(outputFileExtension, ".txt") == 0)
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

void intersection(char *inputFilename, char *secondInputFilename,
                  char *outputFileExtension, char *outputFilename)
{
  Afd *afd1 = mallocAfdFromFile(inputFilename);
  Afd *afd2 = mallocAfdFromFile(secondInputFilename);

  Afd *intersection = generateIntersection(afd1, afd2);

  if (strcmp(outputFileExtension, ".dot") == 0)
  {
    exportAfdDot(outputFilename, intersection);
    freeMemory(afd1);
    freeMemory(afd2);
  }
  else if (strcmp(outputFileExtension, ".txt") == 0)
  {
    exportAfdTxt(outputFilename, intersection);
    freeMemory(afd1);
    freeMemory(afd2);
  }
  else
  {
    printf("Erro ao ler o gerar arquivo: %s%s", outputFilename, outputFileExtension);
    exit(1);
  }
}

void unionOp(char *inputFilename, char *secondInputFilename,
             char *outputFileExtension, char *outputFilename)
{
  Afd *afd1 = mallocAfdFromFile(inputFilename);
  Afd *afd2 = mallocAfdFromFile(secondInputFilename);

  Afd *intersection = generateUnion(afd1, afd2);

  if (strcmp(outputFileExtension, ".dot") == 0)
  {
    exportAfdDot(outputFilename, intersection);
    freeMemory(afd1);
    freeMemory(afd2);
  }
  else if (strcmp(outputFileExtension, ".txt") == 0)
  {
    exportAfdTxt(outputFilename, intersection);
    freeMemory(afd1);
    freeMemory(afd2);
  }
  else
  {
    printf("Erro ao ler o gerar arquivo: %s%s", outputFilename, outputFileExtension);
    exit(1);
  }
}

/**
 * Rotina que trata as entradas do programa via CLI
 * @param argc Número de argumentos inseridos
 * @param argv Lista com argumentos inseridos
 */
void handleOperations(int argc, char *argv[])
{

  if (strcmp(argv[1], "--visualizacao") == 0 && argc == 5)
  {
    visualization(argv[2], argv[3], argv[4]);
  }
  else if (strcmp(argv[1], "--complemento") == 0 && argc == 5)
  {
    complement(argv[2], argv[3], argv[4]);
  }
  else if (strcmp(argv[1], "--intersecao") == 0 && argc == 6)
  {
    intersection(argv[2], argv[3], argv[4], argv[5]);
  }
  else if (strcmp(argv[1], "--uniao") == 0 && argc == 6)
  {
    unionOp(argv[2], argv[3], argv[4], argv[5]);
  }
  else
  {
    printf("Parâmetros não reconhecidos. Verifique se a quantidade fornecida foi correta ou se um input realmente existe no diretório inputs.");
  }
}