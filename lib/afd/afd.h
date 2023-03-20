#ifndef AFD_H
#define AFD_H
#include "../state/state.h"
#include "../transitions/transitions.h"
#include "../alphabet/alphabet.h"

/**
 * Estrutura que representa um AFD
 * @param alphabet Alfabeto reconhecido pelo AFD
 * @param initialState Estado inicial
 * @param states Conjunto de estados
 * @param finalStates Conjunto de estados finais
 * @param transitions Conjunto de transições
 */
typedef struct Afd
{
  Alphabet *alphabet;
  State *initialState;
  StateSet *states;
  StateSet *finalStates;
  TransitionSet *transitions;
} Afd;

Afd *initializeAfd(Alphabet *alphabet,
                   State *initialState,
                   StateSet *states,
                   StateSet *finalStates,
                   TransitionSet *transitions);
Afd *initializeEmptyAfd();
void freeMemory(Afd *afd);
void generateComplement(Afd *afd);
Afd *generateProduct(Afd *afd1, Afd *afd2);
Afd *generateIntersection(Afd *afd1, Afd *afd2);
Afd *generateUnion(Afd *afd1, Afd *afd2);
void *removeUnreachableStatesFromAfd(Afd *afd);
Afd *generateMinimization(Afd *afd);
bool recognizeWord(Afd *afd, char *word);
#endif