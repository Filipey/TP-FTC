#ifndef ALPHABET_H
#define ALPHABET_H

/**
 * Estrutura que simboliza o alfabeto de uma linguagem
 * @param size Quantidade de símbolos no alfabeto
 * @param symbols Todos os símbolos presentes no alfabeto
 */
typedef struct Alphabet
{
  int size;
  char **symbols;
} Alphabet;

Alphabet *initializeAlphabet(int size, char **symbols);
void freeAlphabet(Alphabet *alphabet);

#endif