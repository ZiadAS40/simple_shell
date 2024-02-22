#include "main.h"

/**
 * main - the main function for the simple shell project
 * the reason for dividing the function to small ones is
 * to aviod betty error.
 * @argc: the number of arguements.
 * @argv: array of the arguements start with the file's name.
 *
 * Return: always 0.
 */

int main(int argc, char *argv[])
{
	char *line = NULL;
	char **arg = malloc(sizeof(char *) * 32);
	__pid_t child_pid;
	ssize_t read;
	int r, i = 0;

	(void)argc;
	if (arg == NULL)
	{
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		for (i = 0; i < 32; i++)
			arg[i] = NULL;
		printf("#cisfun$ ");
		read = handleRead(&line, &arg);
		if (read == -1)
			exit(EXIT_SUCCESS);
		child_pid = fork();
		if (child_pid == -1 || read == -2)
			exit(EXIT_FAILURE);
		if (child_pid == 0)
		{
			r = handleChild(line, arg, argv);
			if (r == 0)
			{
				return (0);
			}
		}
		else
			wait(NULL);
	}
	free(line);
	free(arg[0]);
	return (0);
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
ssize_t handleRead(char **line, char ***arg)
{
	size_t n = 0;
	ssize_t read;
	char *token;
	int i = 0;

	read = getline(line, &n, stdin);

	if (read > 0 && (*line)[read - 1] == '\n')
		(*line)[read - 1] = '\0';

	token = strtok((*line), " ");
	while (token != NULL && i < 31)
	{
		(*arg)[i++] = token;
		token = strtok(NULL, " ");
	}

	if (strcmp((*arg)[0], "exit") == 0)
	{
		return (-1);
	}
	(*arg)[i] = NULL;
	handlePath(arg);

	if (read == -1)
	{
		free(*line);
	}
	return (read);
}
/**
 * handleChild - handle the execve function and its error
 * @line: the line readed be getline().
 * @arg: the array of arguements for execve.
 * @argv: the main arguenments for the program.
 * Return: 1 of Success
 * 0 if fails.
 */

int handleChild(char *line, char **arg, char **argv)
{
	int r;

	if (strlen(line) < 1)
		return (0);
	r = execve(arg[0], arg, environ);
	if (r == -1)
	{
		printf("%s: No such file or directory\n", argv[0]);
		return (0);
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

	if (fullPath == NULL)
	{
		free(fullPath);
		return;
	}
	if (cpyPath == NULL)
	{
		free(cpyPath);
		return;
	}
	strcpy(cpyPath, path);
	token = strtok(cpyPath, ":");
	while (token != NULL)
	{
		sprintf(fullPath, "%s/%s", token, (*arg)[0]);

		if (access(fullPath, X_OK) == 0)
		{
			if (fullPath[1] == 117)
				goto breaking_point;
			free((*arg)[0]);
			(*arg)[0] = malloc(sizeof(char) * 1024);
			strcpy((*arg)[0], fullPath);
			free(fullPath);
			return;
		}
breaking_point:
		token = strtok(NULL, ":");
	}
	free(fullPath);
	free(cpyPath);
}
