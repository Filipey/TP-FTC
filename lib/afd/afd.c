#include <stdlib.h>
#include "afd.h"

/**
 * Aloca um AFD em memória com atributos settados
 * @param alphabet Alfabeto do AFD
 * @param initialState Estado Inicial
 * @param states Conjunto de estados
 * @param finalStates Conjunto de estados finais
 * @param transitions Conjunto de transições
 */
Afd *initializeAfd(Alphabet *alphabet,
                   State *initialState,
                   StateSet *states,
                   StateSet *finalStates,
                   TransitionSet *transitions)
{
  Afd *afd = malloc(1 * sizeof(Afd));
  afd->alphabet = alphabet;
  afd->initialState = initialState;
  afd->states = states;
  afd->finalStates = finalStates;
  afd->transitions = transitions;

  return afd;
}

/**
 * Libera memória alocada para um AFD
 * @param afd AFD alocado
 */
void freeMemory(Afd *afd)
{
  free(afd->alphabet);
  free(afd->initialState);
  free(afd->states);
  free(afd->finalStates);
  free(afd->transitions);
}