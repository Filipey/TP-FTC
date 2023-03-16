#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "io.h"

/**
 * Aloca um AFD em memória com base no arquivo de entrada
 * @param filename Nome do arquivo que será gerado
 */
void mallocAfdFromFile(char *filename)
{
  FILE *file = fopen(filename, "rt");

  char *line;
  char buffer[100];
  int lineCount = 0;

  StateSet *statesSet = NULL;
  StateSet *finalStates = NULL;
  TransitionSet *transitions = NULL;
  char **symbols = NULL;
  Alphabet *alphabet = NULL;

  int statesCount = 0;
  int remaningStates = 99;
  int currentStatesSetLastIndex = 0;
  int symbolsCount = 0;
  int remainingSymbols = 99;
  int transitionsCount = 0;
  int remainingTransitions = 99;
  int finalStatesCount = 0;
  int remainingFinalStates = 99;

  if (!file)
  {
    printf("Erro ao ler o arquivo!\n");
    return;
  }

  while (!feof(file))
  {
    line = fgets(buffer, 100, file);
    if (lineCount == 0)
    {
      int setSize = atoi(line);
      statesSet = initializeStateSet(setSize);
      statesCount = atoi(line);
      remaningStates = statesCount;
    }

    if (remaningStates > 0 && lineCount != 0)
    {
      printf("\nLINE: %s", line);
      printf("\nESTADOS QUE PRECISAM SER LIDOS: %d", statesCount);
      printf("\nESTADOS RESTANTES: %d", remaningStates);
      printf("\nESTADOS JÁ LIDOS: %d", statesCount - remaningStates);
      printf("\nPRÓXIMA POSIÇÃO NO ARRAY A SER PREENCHIDA: %d\n", currentStatesSetLastIndex);
      char *stateName = malloc(100 * sizeof(char));
      line[strcspn(line, "\n")] = '\0';
      strcpy(stateName, line);
      State *currentState = createState(stateName, finalStatesCount != 0);
      addStateToSet(currentState, statesSet, currentStatesSetLastIndex);
      printf("\nSTATE ADDED: %s\n", statesSet->states[currentStatesSetLastIndex]->name);
      // strncpy(statesSet->states[currentStatesSetLastIndex]->name,
      //         currentState->name, strlen(currentState->name)); // Atualizando valor do estado para dentro do conjunto
      currentStatesSetLastIndex++;
      remaningStates--;
    }

    if (remainingSymbols > 0 && remaningStates == 0)
    {
      printf("LINHA ATUAL: %s", line);
      symbolsCount = atoi(fgets(buffer, 100, file));
      remainingSymbols = symbolsCount;
      symbols = malloc(atoi(line) * sizeof(char *));
      printf("REMAINING SYMBOLS: %d", remainingSymbols);
      printf("SYMBOLS COUNT: %d", symbolsCount);

      for (int i = 0; i < symbolsCount; i++)
      {
        char *symbol = fgets(buffer, 100, file);
        symbols[i] = symbol;
        remainingSymbols--;
      }

      alphabet = initializeAlphabet(atoi(line), symbols);
    }

    if (remainingTransitions > 0 && remainingSymbols == 0)
    {
      transitionsCount = atoi(fgets(buffer, 100, file));
      transitions = initializeTransitionsSet(transitionsCount);
      remainingTransitions = transitionsCount;

      for (int i = 0; i < transitionsCount; i++)
      {
        remainingTransitions--;
        char *transitionString = fgets(buffer, 100, file);
        char *sourceStateString = malloc(20 * sizeof(char *));
        char *symbol = malloc(20 * sizeof(char *));
        char *sinkStateString = malloc(20 * sizeof(char *));
        sscanf(transitionString, "%s %s %s", sourceStateString, symbol, sinkStateString);
        State *sourceState = findStateInSet(sourceStateString, statesSet);
        State *sinkState = findStateInSet(sinkStateString, statesSet);
        printf("FOUNDED SOURCE STATE: %s", sourceState->name);
        printf("FOUNDED SINK STATE: %s", sinkState->name);
        Transition *currentTransition = createTransition(symbol, sourceState, sinkState);
        addTransitionToSet(currentTransition, transitions);
        // printf("\nAllocated Transition: %s to %s with symbol = %s", currentTransition->source->name, currentTransition->sink->name, currentTransition->symbol);
      }
    }

    lineCount++;
  }

  fclose(file);
}