#include "main.h"

/**
 * main - the main function for the simple shell project
 * @argc: the number of arguments.
 * @argv: array of the arguments start with the file's name.
 *
 * Return: always 0.
 */
int main(int argc, char *argv[])
{
    char *line = NULL;
    char **arg = malloc(sizeof(char *) * 32);
    __pid_t child_pid;
    ssize_t read;
    size_t len = 0;

    (void)argc;
    if (arg == NULL)
    {
        exit(EXIT_FAILURE);
    }
    while (1)
    {
        printf("$ ");
        fflush(stdout);
        read = getline(&line, &len, stdin);
        if (read == -1)
        {
            free(line);
            freeArr(&arg);
            exit(EXIT_SUCCESS);
        }
        if (read > 0 && line[read - 1] == '\n')
        {
            line[read - 1] = '\0';
        }
        if (handleRead(line, &arg))
        {
            child_pid = fork();
            if (child_pid == -1)
            {
                free(line);
                freeArr(&arg);
                exit(EXIT_FAILURE);
            }
            if (child_pid == 0)
            {
                if (handleChild(line, arg, argv) == -1)
                {
                    exit(EXIT_FAILURE); 
                }
            }
            else
            {
                wait(NULL);
            }
        }
    }


    free(line);
    freeArr(&arg);
    return (0);
}

/**
 * handleRead - processes the input line and tokenizes arguments for execve().
 * @line: the input line.
 * @arg: the arguments array to modify from a null array to an array containing tokens.
 * Return: 0 to continue, 1 to proceed with forking and execution.
 */
ssize_t handleRead(char *line, char ***arg)
{
    char *token;
    int i = 0;

    if (*line == '\0')
    {
        return 0;
    }

    token = strtok(line, " "); 

    while (token != NULL && i < 31) 
    {
        (*arg)[i++] = token;
        token = strtok(NULL, " ");
    }
    (*arg)[i] = NULL;

    if (strcmp((*arg)[0], "exit") == 0)
    {
        freeArr(arg);
        exit(EXIT_SUCCESS);
    }
    if (strcmp((*arg)[0], "env") == 0 && (*arg)[1] == NULL)
    {
        printEnviron();
        return 0;
    }

    handlePath(arg);
    return 1;
}

/**
 * handleChild - Executes the command in a child process.
 * @line: The command line input.
 * @arg: Tokenized arguments for the command.
 * @argv: The original argv from main, for error messages.
 * Return: -1 on failure, does not return on success due to execve.
 */
int handleChild(char *line, char **arg, char **argv)
{
	(void)line;
	(void)argv;
    if (execve(arg[0], arg, environ) == -1)
    {
        fprintf(stderr, "%s: No such file or directory\n", arg[0]);
        return (-1);
    }
    return (1);
}

/**
 * handlePath - Modifies the command to include the full path if necessary.
 * @arg: Pointer to the array of arguments.
 * Note: This function modifies the first argument in place if a path is found.
 */
void handlePath(char ***arg)
{
    char *path = getenv("PATH");
    char fullPath[1024];
    char *token = strtok(path, ":");
    struct stat st;

    while (token != NULL)
    {
        snprintf(fullPath, sizeof(fullPath), "%s/%s", token, (*arg)[0]);
        if (stat(fullPath, &st) == 0)
        {
            (*arg)[0] = strdup(fullPath);
            return;
        }
        token = strtok(NULL, ":");
    }
}

/**
 * printEnviron - Prints the current environment variables.
 */
void printEnviron(void)
{
	int i;
    for (i = 0; environ[i] != NULL; i++)
    {
        printf("%s\n", environ[i]);
    }
}

/**
 * freeArr - Frees an array of strings.
 * @arr: The array to free.
 */
void freeArr(char ***arr)
{
	int i;
    if (arr != NULL && *arr != NULL)
    {
        for (i = 0; (*arr)[i] != NULL; i++)
        {
            free((*arr)[i]);
        }
        free(*arr);
        *arr = NULL;
    }
}
