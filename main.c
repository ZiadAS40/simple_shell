#include "main.h"

extern char **environ;

void sig_handler(int sig);

/**
 * sig_handler - Prints a new prompt upon a signal.
 * @sig: The signal.
 */
void sig_handler(int sig)
{
	char *newprompt = "\n$ ";

	(void)sig;
	signal(SIGINT, sig_handler);
	write(STDOUT_FILENO, newprompt, 3);
}

/**
 * main - the main function for the simple shell project.
 * @argc: the number of arguments.
 * @argv: array of the arguments starting with the file's name.
 *
 * Return: always 0.
 */
int main(int argc, char *argv[])
{
	char *line = NULL;
	char **arg;
	__pid_t child_pid;
	ssize_t nread = 0;
	size_t len = 0;

	(void)argc;
	signal(SIGINT, sig_handler);

	while (1)
	{
		write(STDOUT_FILENO, "$ ", 2);
		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
			{
				write(STDOUT_FILENO, "\n", 1);
			}
				break;
		}
		if (*line == '\n')
		{
			continue;
		}
		if (nread > 0 && line[nread - 1] == '\n')
			line[nread - 1] = '\0';
		nread = handleRead(line, &arg);
		if (nread == 0)
			continue;
		child_pid = fork();
		if (child_pid == -1)
			exit(EXIT_FAILURE);
		if (child_pid == 0)
		{
			if (handleChild(&line, arg, &argv) == -1)
				exit(EXIT_FAILURE);
		}
		else
			wait(NULL);
	}
	free(line);
	return (0);
}

/**
 * freeArr - freeing an array.
 * @arg: a pointer to the array (array of strings).
 */
void freeArr(char ***arg)
{
	int i;

	for (i = 0; (*arg)[i] != NULL; i++)
	{
		if ((*arg)[i])
			free((*arg)[i]);
		(*arg)[i] = NULL;
	}
	free(*arg);
}
/**
 * handleRead - handle the getline process and tokenize
 * the arguments for execve().
 * @line: a pointer to the line to modify it;
 * @arg: a pointer to the arg array to modiry it
 * modify from a null array to array contain the
 * the file's name is the first element and the arguments
 * Return: -1 if fails
 * the number of read characters if success.
 */
ssize_t handleRead(char *line, char ***arg)
{

	char *token;
	int i = 0;

	(*arg) = malloc(sizeof(char *) * 32);
	if (!(*arg))
		freeArr(arg);
	token = strtok(line, " ");

	while (token != NULL && i < 31)
	{
		(*arg)[i++] = token;
		token = strtok(NULL, " ");
	}

	(*arg)[i] = NULL;
	if (strcmp((*arg)[0], "exit") == 0)
		exit(EXIT_SUCCESS);
	if (strcmp((*arg)[0], "env") == 0 && (*arg)[1] == NULL)
	{
		printEnviron();
		return (0);
	}
	if ((*arg)[0][0] != '/' && (*arg)[0][0] != '.')
		handlePath(arg);

	return (1);
}
/**
 * handleChild - handle the execve function and its error
 * @line: the line readed be getline().
 * @arg: the array of arguements for execve.
 * @argv: the main arguenments for the program.
 * Return: 1 of Success
 * 0 if fails.
 */

int handleChild(char **line, char **arg, char ***argv)
{
	int r;

	if (strlen(*line) < 1)
	{
		return (0);
	}
	if (arg[0] != NULL)
		r = execve((arg)[0], (arg), environ);
	if (r == -1)
	{
		printf("%s: No such file or directory\n", (*argv)[0]);
		return (-1);
	}
	return (1);
}
/**
 * handlePath - handle the command if have no path
 * @arg: pointer to arg(the plain).
 */
void handlePath(char ***arg)
{
	char *path = getenv("PATH");
	char *fullPath = malloc(sizeof(char) * 1024);
	char *token;
	char *cpyPath = malloc(sizeof(char) * strlen(path) + 1);

	if (!fullPath)
	{
		free(cpyPath);
		return;
	}
	if (!cpyPath)
	{
		free(fullPath);
		return;
	}
	strcpy(cpyPath, path);
	token = strtok(cpyPath, ":");
	while (token != NULL)
	{
		sprintf(fullPath, "%s/%s", token, (*arg)[0]);

		if (access(fullPath, X_OK) == 0)
		{
			(*arg)[0] = strdup(fullPath);
			break;
		}
		token = strtok(NULL, ":");
	}
	free(fullPath);
	free(cpyPath);
}
/**
 * printEnviron - print the current environment.
 */
void printEnviron(void)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}
}