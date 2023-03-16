#ifndef IO_H
#define IO_H
#include "../afd/afd.h"

Afd *mallocAfdFromFile(char *filename);
void exportAfdDot(char *filename);
void exportAcceptedWords(char *filename);
void exportAfdTxt(Afd *afd, char *filename);
void writeStatesInTxt(StateSet *stateSet, FILE *file);
void writeSymbolsInTxt(Alphabet *alphabet, FILE *file);
void writeTransitionsInTxt(TransitionSet *transitionSet, FILE *file);
void writeFinalStatesInTxt(StateSet *stateSet, FILE *file);

#endif