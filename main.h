#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

extern char **environ;

int handleChild(char *line,char **arg, char **argv);
ssize_t handleRead(char **line, char ***arg);
void handlePath(char ***arg);
ssize_t _getline(char **lineptr, size_t *len, FILE *stream);
int exitCheck(char *token);
void printEnviron(void);
char *_strtok(char *line, char sep);
void custom_realloc(char **buffer, int *buffer_size);
#endif