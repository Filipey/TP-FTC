#include <stdlib.h>
#include <stdio.h>
#include "state.h"

/**
 * Aloca um novo estado na memória
 * @param name nome do estado
 * @param isFinal simboliza se é um estado final
 * @return Estado alocado
 */
State *createState(char *name, bool isFinal)
{
  State *newState = (State *)malloc(1 * sizeof(State));

  newState->name = name;
  newState->isFinal = isFinal;

  return newState;
}

/**
 * Aloca um conjunto de estados em memoria para todos os estados
 * @param size Quantidade de estados
 * @return Conjunto alocado em memória
 */
StateSet *initializeStateSet(int size)
{
  StateSet *set = malloc(1 * sizeof(StateSet));
  set->size = size;
  set->states = malloc(size * sizeof(State));

  return set;
}

/**
 * Adiciona um novo estado ao conjunto de estados
 * @param state estado a ser adicionado
 * @param set conjunto de estados
 */
void addStateToSet(State *state, StateSet *set)
{
  for (int i = 0; i < set->size; i++)
  {
    if (set->states[i] == NULL)
    {
      set->states[i] = state;
      return;
    }
  }
}