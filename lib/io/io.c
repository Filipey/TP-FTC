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
  char path[100];
  snprintf(path, sizeof(path), "inputs/%s", filename);
  FILE *file = fopen(path, "rt");

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
        symbol[strcspn(symbol, "\n")] = '\0';
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

/**
 * Escreve a todos os estados, um por linha, no arquivo txt
 * @param stateSet Conjunto de estados
 * @param file Ponteiro para o arquivo
 */
void writeStatesInTxt(StateSet *stateSet, FILE *file)
{
  for (int i = 0; i < stateSet->size; i++)
  {
    fprintf(file, "%s\n", stateSet->states[i]->name);
  }
}

/**
 * Escreve todos os símbolos do alfabeto, um por linha, no arquivo txt
 * @param alphabet Alfabeto do AFD
 * @param file Ponteiro para o arquivo
 */
void writeSymbolsInTxt(Alphabet *alphabet, FILE *file)
{
  for (int i = 0; i < alphabet->size; i++)
  {
    fprintf(file, "%s\n", alphabet->symbols[i]);
  }
}

/**
 * Escreve todas as transições do AFD, uma por linha, no arquivo txt
 * @param transitionsSet Conjunto de transições do AFD
 * @param file Ponteiro para o arquivo
 */
void writeTransitionsInTxt(TransitionSet *transitionsSet, FILE *file)
{
  for (int i = 0; i < transitionsSet->size; i++)
  {
    char *sourceState = transitionsSet->transitions[i]->source->name;
    char *readedSymbol = transitionsSet->transitions[i]->symbol;
    char *sinkState = transitionsSet->transitions[i]->sink->name;
    fprintf(file, "%s %s %s\n", sourceState, readedSymbol, sinkState);
  }
}

/**
 * Escreve os estados finais do AFD, um por linha, no arquivo txt
 * @param statesSet Conjuntos de estados finais
 * @param file Ponteiro para o arquivo
 */
void writeFinalStatesInTxt(StateSet *statesSet, FILE *file)
{
  for (int i = 0; i < statesSet->size; i++)
  {
    fprintf(file, "%s\n", statesSet->states[i]->name);
  }
}

/**
 * Exporta o AFD em formato .txt
 * @param filename Nome do arquivo a ser exportado
 * @param afd AFD em memória a ser escrito no arquivo
 */
void exportAfdTxt(char *filename, Afd *afd)
{
  char path[100];
  snprintf(path, sizeof(path), "outputs/%s", filename);
  FILE *file = fopen(path, "wt");

  if (file == NULL)
  {
    printf("Erro ao escrever arquivo!");
    exit(1);
  }

  fprintf(file, "%d\n", afd->states->size);       // Quantidade de Estados
  writeStatesInTxt(afd->states, file);            // Escreve cada Estado em uma linha
  fprintf(file, "%d\n", afd->alphabet->size);     // Quantidade de símbolos
  writeSymbolsInTxt(afd->alphabet, file);         // Escreve cada símbolo em uma linha
  fprintf(file, "%d\n", afd->transitions->size);  // Quantidade de transições
  writeTransitionsInTxt(afd->transitions, file);  // Escreve cada transição em uma linha
  fprintf(file, "%s\n", afd->initialState->name); // Escreve o Estado inicial
  fprintf(file, "%d\n", afd->finalStates->size);  // Escreve a quantidade de estados finais
  writeFinalStatesInTxt(afd->finalStates, file);  // Escreve cada Estado final em uma linha

  fclose(file);
}

/**
 * Escreve em um arquivo .dot o template para um AFD
 * @param filename Nome do arquivo .dot
 */
FILE *writeDotTemplate(char *filename)
{
  char path[100];
  snprintf(path, sizeof(path), "outputs/%s", filename);
  FILE *file = fopen(path, "wt");

  fprintf(file, "digraph finite_state_machine {\n");
  fprintf(file, "  fontname=\"Helvetica, Arial, sans-serif\"\n");
  fprintf(file, "  node [fotname=\"Helvetica, Arial, sans-serif\"]\n");
  fprintf(file, "  edge [fontname=\"Helvetica, Arial, sans-serif\"]\n");
  fprintf(file, "  rankdir=LR\n");

  return file;
}

/**
 * Escreve os estados finais no arquivo .dot
 * @param finalStates Conjunto de estados finais
 * @param file Ponteiro para o arquivo
 */
void writeFinalStatesInDot(StateSet *finalStates, FILE *file)
{
  char *finalStatesString = malloc(200 * sizeof(char));
  memset(finalStatesString, 0, 200 * sizeof(char)); // Remove lixo de memória se houver

  for (int i = 0; i < finalStates->size; i++)
  {
    char *currentState = finalStates->states[i]->name;
    if (i == finalStates->size - 1) // Se for o último estado final, não é necessário espaçamento
    {
      strcat(finalStatesString, currentState);
    }
    else
    {
      strcat(currentState, " ");
      strcat(finalStatesString, currentState);
    }
  }

  fprintf(file, "  node [shape = doublecircle]; %s;\n", finalStatesString);
  fprintf(file, "  node [shape = circle];\n");
  free(finalStatesString);
}

/**
 * Escreve as transições do AFD no arquivo .dot
 * @param transitionSet Conjunto de transições do AFD
 * @param file Ponteiro para o arquivo
 */
void writeTransitionsInDot(TransitionSet *transitionSet, FILE *file)
{
  for (int i = 0; i < transitionSet->size; i++)
  {
    char *sourceState = transitionSet->transitions[i]->source->name;
    char *sinkState = transitionSet->transitions[i]->sink->name;
    char *symbol = transitionSet->transitions[i]->symbol;

    fprintf(file, "  %s -> %s [label = \"%s\"];\n", sourceState, sinkState, symbol);
  }
  fprintf(file, "}");
}

/**
 * Exporta o AFD em memória em um arquivo .dot
 * @param filename Nome do arquivo
 * @param afd AFD em memória
 */
void exportAfdDot(char *filename, Afd *afd)
{
  FILE *file = writeDotTemplate(filename);
  writeFinalStatesInDot(afd->finalStates, file);
  writeTransitionsInDot(afd->transitions, file);
  fclose(file);
}