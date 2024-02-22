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
	int r;

	(void)argc;
	if (arg == NULL)
	{
		free(arg);
		exit(EXIT_FAILURE);
	}
	while (1)
	{
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
	(*arg)[i] = NULL;
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
