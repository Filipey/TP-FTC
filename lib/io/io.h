#ifndef IO_H
#define IO_H
#include "../afd/afd.h"

void generateAfdFromFile(char *filename);
State *readState(char *line);
Transition *readTransition(char *line);
char *readSymbol(char *line);

#endif