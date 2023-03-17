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
  free(state->name);
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

  return set;
}

/**
 * Libera memória para um conjunto de Estados alocados
 */
void freeStateSet(StateSet *set)
{
  for (int i = 0; i < set->size; i++)
  {
    freeState(set->states[i]);
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
  set->states[index] = malloc(sizeof(State));
  set->states[index]->name = malloc(100 * sizeof(char));
  strcpy(set->states[index]->name, state->name);
  set->states[index]->isFinal = state->isFinal;
}

/**
 * Remove um Estado de um determinado conjunto
 * @param state Estado a ser removido
 * @param set Conjunto de Estados
 */
void removeStateFromSet(State *state, StateSet *set)
{
  for (int i = 0; i < set->size; i++)
  {
    if (strcmp(set->states[i]->name, state->name) == 0)
    {
      free(set->states[i]->name);
      free(set->states[i]);
    }
  }
}

/**
 * Busca por um Estado no conjunto de estados
 * @param stateName Nome do Estado
 * @param set Conjunto de Estados
 */
State *findStateInSet(char *stateName, StateSet *set)
{
  for (int i = 0; i < set->size; i++)
  {
    if (strcmp(set->states[i]->name, stateName) == 0)
    {
      return set->states[i];
    }
  }
}

/**
 * Retorna o index do Estado no conjunto
 * @param state Estado a ser encontrado
 * @param set Conjunto de Estados
 */
int findStateIndex(State *state, StateSet *set)
{
  for (int i = 0; i < set->size; i++)
  {
    if (strcmp(set->states[i]->name, state->name) == 0)
    {
      return i;
    }
  }
}

/**
 * Atualiza o rótulo de um Estado
 */
State *updateStateFinalCondition(State *state, bool newCondition)
{
  state->isFinal = newCondition;
}