#ifndef IO_H
#define IO_H
#include "../afd/afd.h"

void mallocAfdFromFile(char *filename);
void exportAfdDot(char *filename);
void exportAcceptedWords(char *filename);

#endif