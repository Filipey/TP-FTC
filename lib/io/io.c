#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "io.h"

/**
 * Aloca um AFD em memória com base no arquivo de entrada
 * @param filename Nome do arquivo que será gerado
 * @return AFD alocado em memória
 */
Afd *mallocAfdFromFile(char *filename)
{
  FILE *file = fopen(filename, "rt");

  char *line;
  char buffer[100];
  int lineCount = 0;

  State *initialState = NULL;
  StateSet *statesSet = NULL;
  StateSet *finalStates = NULL;
  TransitionSet *transitionsSet = NULL;
  char **symbols = NULL;
  Alphabet *alphabet = NULL;

  int statesCount = 0;
  int currentStatesSetLastIndex = 0;
  int currentFinalStatesSetIndex = 0;
  int transitionsCount = 0;
  int symbolsCount = 0;
  int finalStatesCount = 0;
  int remaningStates = 99;
  int remainingSymbols = 99;
  int remainingTransitions = 99;
  int remainingFinalStates = 99;
  bool foundedInitialState = false;

  if (!file)
  {
    printf("Erro ao ler o arquivo!\n");
    exit(1);
  }

  while (!feof(file))
  {
    line = fgets(buffer, 100, file);
    if (lineCount == 0) // Leitura da primeira linha
    {
      statesSet = initializeStateSet(atoi(line));
      statesCount = atoi(line);
      remaningStates = statesCount;
    }

    if (remaningStates > 0 && lineCount != 0) // Lendo Estados
    {
      remaningStates--;
      char *stateName = malloc(100 * sizeof(char));
      line[strcspn(line, "\n")] = '\0';
      strcpy(stateName, line);
      State *currentState = createState(stateName, 0);
      addStateToSet(currentState, statesSet, currentStatesSetLastIndex);
      currentStatesSetLastIndex++;
    }

    if (remainingSymbols > 0 && remaningStates == 0) // Lendo Símbolos
    {
      symbolsCount = atoi(fgets(buffer, 100, file));
      remainingSymbols = symbolsCount;
      symbols = malloc(symbolsCount * sizeof(char *));

      for (int i = 0; i < symbolsCount; i++)
      {
        char *symbol = fgets(buffer, 100, file);
        symbols[i] = malloc(strlen(symbol) + 1);
        strcpy(symbols[i], symbol);
        remainingSymbols--;
      }

      alphabet = initializeAlphabet(symbolsCount, symbols);
    }

    if (remainingTransitions > 0 && remainingSymbols == 0) // Lendo Transições
    {
      transitionsCount = atoi(fgets(buffer, 100, file));
      transitionsSet = initializeTransitionsSet(transitionsCount);
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
        Transition *currentTransition = createTransition(symbol, sourceState, sinkState);
        addTransitionToSet(currentTransition, transitionsSet);
      }
    }

    if (!foundedInitialState && remainingTransitions == 0) // Lendo o Estado inicial
    {
      char *stateName = malloc(100 * sizeof(char));
      line = fgets(buffer, 100, file);
      line[strcspn(line, "\n")] = '\0';
      strcpy(stateName, line);
      initialState = findStateInSet(stateName, statesSet);
      foundedInitialState = true;
    }

    if (foundedInitialState && finalStatesCount == 0) // Lendo quantidade de Estados finais
    {
      finalStatesCount = atoi(fgets(buffer, 100, file));
      finalStates = initializeStateSet(finalStatesCount);
      remainingFinalStates = finalStatesCount;
    }

    if (foundedInitialState && finalStatesCount != 0) // Lendo Estados finais
    {
      line = fgets(buffer, 100, file);
      remainingFinalStates--;
      char *stateName = malloc(100 * sizeof(char));
      line[strcspn(line, "\n")] = '\0';
      strcpy(stateName, line);
      State *currentState = findStateInSet(stateName, statesSet);
      updateStateFinalCondition(currentState, true);
      addStateToSet(currentState, finalStates, currentFinalStatesSetIndex);
      currentFinalStatesSetIndex++;
    }

    lineCount++;
  }

  fclose(file);

  return initializeAfd(alphabet, initialState, statesSet,
                       finalStates, transitionsSet);
}