#include "main.h"

/**
 * parser_func - parse the line into an array of commands
 * @line: a pointer to the line read by getline.
 * Return: an array of stings.
 */

char **parser_func(char *line, char **argv)
{
	int buffer_size = 1024, i = 0;
	char **args = malloc(sizeof(char *) * buffer_size);
	char *token;

	if (!args)
		exit(EXIT_FAILURE);

	token = strtok(line, " \t\r\n\a");
	while (token != NULL)
	{
		args[i] = token;
		i++;
		if (i >= buffer_size)
		{
			buffer_size += 1024;
			args = realloc(args, buffer_size * sizeof(char *));
			if (!args)
				exit(EXIT_FAILURE);
		}
		token = strtok(NULL, " \t\r\n\a");
	}
	if (args[0][0] != '/' && args[0][0] != '.')
	{
		token = args[0];
		args[0] = handlePath(args);
	}
	if (args[0] == NULL)
	{
		dprintf(2, "%s: 1: %s: not found", argv[0], token);
		exit(EXIT_FAILURE);
	}
	args[i] = NULL;
	return (args);
}
