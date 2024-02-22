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
void fillNull(char ***arg);
#endif