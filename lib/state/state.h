#ifndef STATE_H
#define STATE_H
#include <stdbool.h>

/**
 * Estrutura que simboliza um estado
 * @param name Nome do estado
 * @param isFinal Simboliza se é um estado final
 */
typedef struct State
{
  char *name;
  bool isFinal;
} State;

/**
 * Estrutura que agrupa todos estados em um conjunto
 * @param size Quantidade de estados
 * @param states Estados no conjunto
 */
typedef struct StateSet
{
  int size;
  State **states;
} StateSet;

State *createState(char *name, bool isFinal);
StateSet *initializeStateSet(int size);
void addStateToSet(State *state, StateSet *set);

#endif