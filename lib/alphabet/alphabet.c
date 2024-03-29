#include "alphabet.h"
#include <stdlib.h>

/**
 * Aloca o alfabeto da linguagem em memória
 * @param size Quantidade de símbolos
 * @param symbols Símbolos do alfabeto
 * @return Alfabeto alocado e com valores settados
 */
Alphabet *initializeAlphabet(int size, char **symbols)
{
  Alphabet *alphabet = malloc(1 * sizeof(Alphabet));
  alphabet->size = size;
  alphabet->symbols = malloc(size * sizeof(char *));
  alphabet->symbols = symbols;

  return alphabet;
}

/**
 * Libera a memória alocada para um alfabeto
 */
void freeAlphabet(Alphabet *alphabet)
{
  for (int i = 0; i < alphabet->size; i++)
  {
    free(alphabet->symbols[i]);
  }

  free(alphabet);
}