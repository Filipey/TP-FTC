#include <stdlib.h>
#include <string.h>
#include "transitions.h"
#include "../afd/afd.h"

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
  set->transitions = malloc(size * sizeof(Transition *));

  return set;
}

/**
 * Adicina uma transição ao conjunto de transições
 * @param transition Transição a ser adicionada
 * @param set Conjunto de transições
 */
void addTransitionToSet(Transition *transition, TransitionSet *set, int index)
{
  set->transitions[index] = malloc(sizeof(Transition));
  set->transitions[index]->source = transition->source;
  set->transitions[index]->sink = transition->sink;
  set->transitions[index]->symbol = malloc(100 * sizeof(char));
  strcpy(set->transitions[index]->symbol, transition->symbol);
}

Transition *findTransitionInSet(char *sourceName, char *symbol, TransitionSet *set)
{
  for (int i = 0; i < set->size; i++)
  {
    Transition *currentTransition = set->transitions[i];
    if (strcmp(currentTransition->source->name, sourceName) == 0 &&
        strcmp(currentTransition->symbol, symbol) == 0)
    {
      return currentTransition;
    }
  }

  return NULL;
}

State *applyTransition(Transition *transition)
{
  return transition->sink;
}

/**
 * Libera memória alocada para uma Transição
 */
void freeTransition(Transition *transition)
{
  free(transition->symbol);
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