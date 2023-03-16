#include <stdlib.h>
#include "transitions.h"

/**
 * Aloca uma transição em memória
 * @param symbol Símbolo lido pela transição
 * @param source Estado atual
 * @param sink Estado de destino
 * @return Transição alocada com valores setados
 */
Transition *createTransition(char *symbol, State *source, State *sink)
{
  Transition *transition = malloc(1 * sizeof(Transition));
  transition->symbol = symbol;
  transition->source = source;
  transition->sink = sink;

  return transition;
}

/**
 * Inicializa um conjunto de transições em memória
 * @param size Quantidade de transições
 * @return Conjunto alocado
 */
TransitionSet *initializeTransitionsSet(int size)
{
  TransitionSet *set = malloc(1 * sizeof(TransitionSet));
  set->size = size;
  set->transitions = malloc(size * sizeof(Transition));

  return set;
}

/**
 * Adicina uma transição ao conjunto de transições
 * @param transition Transição a ser adicionada
 * @param set Conjunto de transições
 */
void addTransitionToSet(Transition *transition, TransitionSet *set)
{
  for (int i = 0; i < set->size; i++)
  {
    if (set->transitions[i] == NULL)
    {
      set->transitions[i] = transition;
      return;
    }
  }
}

/**
 * Libera memória alocada para uma Transição
 */
void freeTransition(Transition *transition)
{
  free(transition);
}

/**
 * Libera memória alocada para um conjunto de transições
 */
void freeTransitionSet(TransitionSet *set)
{
  for (int i = 0; i < set->size; i++)
  {
    freeTransition(set->transitions[i]);
  }

  free(set);
}