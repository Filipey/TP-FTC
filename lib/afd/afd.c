#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "afd.h"
#include "../utils/utils.h"

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

Afd *initializeEmptyAfd()
{
  Afd *afd = malloc(1 * sizeof(Afd));
  afd->alphabet = NULL;
  afd->finalStates = NULL;
  afd->initialState = NULL;
  afd->states = NULL;
  afd->transitions = NULL;

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

/**
 * Gerar um novo AFD resultante do produto entre os AFDs de entrada
 * @param afd1 Primeiro AFD de entrada
 * @param afd2 Segundo AFD de entrada
 * @return Novo AFD que representa o produtos entre afd1 e afd2
 */
Afd *generateProduct(Afd *afd1, Afd *afd2)
{
  int totalStates = afd1->states->size * afd2->states->size;
  int totalSymbols = afd1->alphabet->size;
  int totalTransactions = totalStates * totalSymbols;

  Afd *product = initializeEmptyAfd();
  product->alphabet = initializeAlphabet(totalSymbols, afd1->alphabet->symbols);
  product->states = initializeStateSet(totalStates);
  product->transitions = initializeTransitionsSet(totalTransactions);

  int productStateSetIndex = 0;
  int productFinalStateSetIndex = 0;
  int productTransationsSetIndex = 0;

  for (int i = 0; i < afd1->states->size; i++)
  {
    State *currentAfd1State = afd1->states->states[i];
    for (int j = 0; j < afd2->states->size; j++)
    {
      State *currentAfd2State = afd2->states->states[j];
      char *stateName = malloc(100 * sizeof(char));
      stateName[strcspn(stateName, "\n")] = '\0';
      sprintf(stateName, "%s, %s", currentAfd1State->name, currentAfd2State->name);
      State *concattedState = createState(stateName, false);
      addStateToSet(concattedState, product->states, productStateSetIndex);

      if (strcmp(currentAfd1State->name, afd1->initialState->name) == 0 &&
          strcmp(currentAfd2State->name, afd2->initialState->name) == 0)
      // Se ambos Estados forem iniciais, a junção deles será o Estado inicial do produto
      {
        char *initialStateName = malloc(100 * sizeof(char));
        initialStateName[strcspn(initialStateName, "\n")] = '\0';
        sprintf(initialStateName, "%s, %s", currentAfd1State->name, currentAfd2State->name);
        product->initialState = createState(initialStateName, true);
      }
      productStateSetIndex++;
    }
  }

  int transitionSetIndex = 0;
  for (int i = 0; i < product->states->size; i++)
  {
    State *currentState = product->states->states[i];
    char **stateNameBreak = breakStateNameWithComma(currentState->name);
    for (int j = 0; j < product->alphabet->size; j++)
    {
      char *symbol = product->alphabet->symbols[j];

      Transition *sourceTransition = findTransitionInSet(stateNameBreak[0], symbol, afd1->transitions);
      Transition *sinkTransition = findTransitionInSet(stateNameBreak[1], symbol, afd2->transitions);

      if (sourceTransition == NULL || sinkTransition == NULL)
      {
        product->transitions->size--;
        break;
      }

      State *sourceAppliedTransition = applyTransition(sourceTransition);
      State *sinkAppliedTransition = applyTransition(sinkTransition);

      char *resultStateName = malloc(100 * sizeof(char));
      resultStateName[strcspn(resultStateName, "\n")] = '\0';
      sprintf(resultStateName, "%s, %s", sourceAppliedTransition->name, sinkAppliedTransition->name);

      State *sinkResultState = findStateInSet(resultStateName, product->states);

      Transition *resultTransition = createTransition(symbol, currentState, sinkResultState);
      addTransitionToSet(resultTransition, product->transitions, transitionSetIndex);
      transitionSetIndex++;
    }
  }

  return product;
}

/**
 * Gera um novo AFD com a interseção dos AFDs de entrada
 * @param afd1 Primeiro AFD de entrada
 * @param afd2 Segundo AFD de entrada
 * @return AFD que aceita a interseção das linguagens de entrada
 */
Afd *generateIntersection(Afd *afd1, Afd *afd2)
{
  Afd *product = generateProduct(afd1, afd2);
  int totalFinalStates = afd1->finalStates->size * afd2->finalStates->size;
  product->finalStates = initializeStateSet(totalFinalStates);

  int productFinalStateSetIndex = 0;
  for (int i = 0; i < afd1->states->size; i++)
  {
    State *currentAfd1State = afd1->states->states[i];
    for (int j = 0; j < afd2->states->size; j++)
    {
      State *currentAfd2State = afd2->states->states[j];
      if (currentAfd1State->isFinal && currentAfd2State->isFinal)
      // Se ambos Estados forem finais, a junção deles será um Estado final do produto de interseção
      {
        char *newFinalStateName = malloc(100 * sizeof(char));
        newFinalStateName[strcspn(newFinalStateName, "\n")] = '\0';
        sprintf(newFinalStateName, "%s, %s", currentAfd1State->name, currentAfd2State->name);
        State *finalState = createState(newFinalStateName, true);
        addStateToSet(finalState, product->finalStates, productFinalStateSetIndex);
        productFinalStateSetIndex++;
      };
    }
  }

  return product;
}

/**
 * Gera um novo AFD com a união dos AFDs de entrada
 * @param afd1 Primeiro AFD de entrada
 * @param afd2 Segundo AFD de entrada
 * @return AFD que aceita a união das linguagens de entrada
 */
Afd *generateUnion(Afd *afd1, Afd *afd2)
{
  Afd *product = generateProduct(afd1, afd2);
  int totalFinalStates = (afd1->finalStates->size * getTotalOfNonFinalStates(afd2->states)) +
                         (getTotalOfNonFinalStates(afd1->states) * afd2->finalStates->size) + (afd1->finalStates->size * afd2->finalStates->size);

  product->finalStates = initializeStateSet(totalFinalStates);

  int productFinalStateSetIndex = 0;
  for (int i = 0; i < afd1->states->size; i++)
  {
    State *currentAfd1State = afd1->states->states[i];
    for (int j = 0; j < afd2->states->size; j++)
    {

      State *currentAfd2State = afd2->states->states[j];
      if (currentAfd1State->isFinal || currentAfd2State->isFinal)
      // Se ao menos um Estado for finais, a junção deles será um Estado final do produto de união
      {
        char *newFinalStateName = malloc(100 * sizeof(char));
        newFinalStateName[strcspn(newFinalStateName, "\n")] = '\0';
        sprintf(newFinalStateName, "%s, %s", currentAfd1State->name, currentAfd2State->name);
        State *finalState = createState(newFinalStateName, true);
        addStateToSet(finalState, product->finalStates, productFinalStateSetIndex);
        productFinalStateSetIndex++;
      };
    }
  }

  return product;
}

Afd *generateMinimization(Afd *afd)
{
}

bool recognizeWord(Afd *afd, char *word)
{
  State *currentState = afd->initialState;

  for (int i = 0; i < strlen(word); i++)
  {
    char *symbol = getCharAtIndex(word, i);
    Transition *currentTransition = findTransitionInSet(currentState->name, symbol, afd->transitions);
    currentState = applyTransition(currentTransition);
    free(symbol);
  }

  if (currentState->isFinal)
  {
    return true;
  }

  return false;
}