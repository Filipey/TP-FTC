#ifndef CLI_H
#define CLI_H

void handleOperations(int argc, char *argv[]);
void visualization(char *inputFilename, char *outputFileExtension, char *outputFilename);
void complement(char *inputFilename, char *outputFileExtension, char *outputFilename);
void intersection(char *firstInputFilename, char *secondInputFilename,
                  char *outputFileExtension, char *outputFilename);
void unionOp(char *firstInputFilename, char *secondInputFilename,
             char *outuputFileExtension, char *outputFilename);
void recognition(char *inputFilename, char *outputFilename, char *afdFilename);
#endif