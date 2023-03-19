#ifndef UTILS_H
#define UTILS_H

char *strTrim(char *string);
char **breakStateNameWithComma(char *stateName);
char *addBrackets(char *string);
void removeCommaAndAddUnderline(char *string);
char *getCharAtIndex(char *str, int index);

#endif