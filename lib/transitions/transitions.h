#ifndef TRANSITIONS_H
#define TRANSITIONS_H
#include "../state/state.h"

/**
 * Estrutura que simboliza transições
 * @param symbol Símbolo lido pela transição
 * @param source Estado atual
 * @param sink Estado de destino
 */
typedef struct Transition
{
  char *symbol;
  State *source;
  State *sink;
} Transition;

/**
 * Estrutura que agrupa todas transições em um conjunto
 * @param size Quantidade de transições
 * @param transitions Transições do conjunto
 */
typedef struct TransitionSet
{
  int size;
  Transition **transitions;
} TransitionSet;

Transition *createTransition(char *symbol, State *source, State *sink);
TransitionSet *initializeTransitionsSet(int size);
void addTransitionToSet(Transition *transition, TransitionSet *set, int index);
State *applyTransition(Transition *transition);
Transition *findTransitionInSet(char *sourceName, char *symbol, TransitionSet *set);
void freeTransition(Transition *transition);
void freeTransitionSet(TransitionSet *set);

#endif