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
void freeState(State *state);
StateSet *initializeStateSet(int size);
void freeStateSet(StateSet *set);
void addStateToSet(State *state, StateSet *set, int index);
void removeStateFromSet(State *state, StateSet *set);
int findStateIndex(State *state, StateSet *set);
State *findStateInSet(char *stateName, StateSet *set);
State *updateStateFinalCondition(State *state, bool newCondition);
int getTotalOfNonFinalStates(StateSet *set);

#endif