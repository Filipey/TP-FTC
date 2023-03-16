#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "state.h"

/**
 * Aloca um novo estado na memória
 * @param name nome do estado
 * @param isFinal simboliza se é um estado final
 * @return Estado alocado
 */
State *createState(char *name, bool isFinal)
{
  State *newState = malloc(1 * sizeof(State));

  newState->name = name;
  newState->isFinal = isFinal;

  return newState;
}

/**
 * Libera memória para um Estado alocado
 */
void freeState(State *state)
{
  free(state);
}

/**
 * Aloca um conjunto de estados vazio em memoria para todos os estados
 * @param size Quantidade de estados
 * @return Conjunto alocado em memória
 */
StateSet *initializeStateSet(int size)
{
  StateSet *set = malloc(1 * sizeof(StateSet));
  set->size = size;
  set->states = malloc(size * sizeof(State *));

  for (int i = 0; i < set->size; i++)
  {
    set->states[i] = malloc(sizeof(State));
    set->states[i]->name = malloc(100 * sizeof(char));
    strncpy(set->states[i]->name, "", 1);
    set->states[i]->isFinal = false;
  }

  return set;
}

/**
 * Libera memória para um conjunto de Estados alocados
 */
void freeStateSet(StateSet *set)
{
  for (int i = 0; i < set->size; i++)
  {
    free(set->states[i]);
  }

  free(set);
}

/**
 * Adiciona um novo estado ao conjunto de estados
 * @param state Estado a ser adicionado
 * @param set Conjunto de Estados
 */
void addStateToSet(State *state, StateSet *set, int index)
{
  set->states[index] = state;
}

/**
 * Busca por um Estado no conjunto de estados
 * @param stateSymbol Nome do Estado
 * @param set Conjunto de Estados
 */
State *findStateInSet(char *stateSymbol, StateSet *set)
{
  for (int i = 0; i < set->size; i++)
  {
    if (set->states[i]->name == stateSymbol)
    {
      return set->states[i];
    }
  }
}