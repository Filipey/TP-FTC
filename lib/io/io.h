#ifndef IO_H
#define IO_H
#include "../afd/afd.h"

Afd *mallocAfdFromFile(char *filename);
void exportAfdDot(char *filename, Afd *afd);
FILE *writeDotTemplate(char *filename);
void exportAcceptedWords(char *filename);
void exportAfdTxt(char *filename, Afd *afd);
void writeStatesInTxt(StateSet *stateSet, FILE *file);
void writeSymbolsInTxt(Alphabet *alphabet, FILE *file);
void writeTransitionsInTxt(TransitionSet *transitionSet, FILE *file);
void writeFinalStatesInTxt(StateSet *stateSet, FILE *file);
void writeInitialStateInDot(State *state, FILE *file);
void writeFinalStatesInDot(StateSet *finalStates, FILE *file);
void writeTransitionsInDot(TransitionSet *transitionSet, FILE *file);
char *readWords(FILE *file, Afd *afd, int *totalWords);
void writeWordIsRecognized(Afd *afd, char *inputFilename, char *outputFilename);

#endif