#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

char *strTrim(char *string)
{
  while (*string == ' ')
  {
    string++;
  }

  char *end = string + strlen(string) - 1;
  while (end > string && *end == ' ')
  {
    end--;
  }
  *(end + 1) = '\0';

  return string;
}

char **breakStateNameWithComma(char *stateName)
{
  char copy[200];
  strcpy(copy, stateName);

  char *token = strtok(copy, ",");
  char **strings = malloc(2 * sizeof(char *));

  int i = 0;
  while (token != NULL)
  {
    strings[i] = malloc(strlen(token) + 1);
    strcpy(strings[i], strTrim(token));
    token = strtok(NULL, ",");
    i++;
  }

  return strings;
}

char *addBrackets(char *string)
{
  int n = strlen(string);
  char *newStr = (char *)malloc((n + 3) * sizeof(char));

  newStr[0] = '{';
  strcpy(newStr + 1, string);
  newStr[n + 1] = '}';
  newStr[n + 2] = '\0';

  return newStr;
}

void removeCommaAndAddUnderline(char *string)
{
  int n = strlen(string);
  int j = 0;

  for (int i = 0; i < n; i++)
  {
    if (string[i] == ',')
    {
      string[j] = '_';
    }
    else if (string[i] != ' ')
    {
      string[j] = string[i];
    }

    if (string[i] != ' ')
    {
      j++;
    }
  }

  string[j] = '\0';
}
