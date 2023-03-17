#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
 * @param afd AFD em memória
 */
void freeMemory(Afd *afd)
{
  freeStateSet(afd->states);
  freeAlphabet(afd->alphabet);
  freeTransitionSet(afd->transitions);
}

/**
 * Gera o complemento de um AFD de entrada
 * @param afd AFD de entrada
 */
void generateComplement(Afd *afd)
{
  StateSet *newFinalStates = initializeStateSet(afd->states->size - afd->finalStates->size);
  int newFinalStatesIndex = 0;

  for (int i = 0; i < afd->states->size; i++)
  {
    if (!afd->states->states[i]->isFinal)
    {
      updateStateFinalCondition(afd->states->states[i], true);
      addStateToSet(afd->states->states[i], newFinalStates, newFinalStatesIndex);
      newFinalStatesIndex++;
    }
  }

  afd->finalStates = newFinalStates;
}