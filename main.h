#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <signal.h>

extern char **environ;


int handleXcution(char **args, char **argv);
char **parser_func(char *line, char **argv);
void innerMain(char **argv);
char *handlePath(char **arg);






/* Old Mian.h 
int handleChild(char **line, char **arg, char ***argv);
ssize_t handleRead(char **line, char ***arg);
void handlePath(char ***arg);
ssize_t _getline(char **lineptr, size_t *len, FILE *stream);
void printEnviron(void);
char *_strtok(char *line, char sep);
void custom_realloc(char **buffer, int *buffer_size);
void handleExit(char ***arg);
void freeArr(char ***arg);
*/


#endif
