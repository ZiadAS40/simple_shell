#include "main.h"
void freeArr(char ***args);
/**
 * main - the main function for the simple shell project.
 * @argc: the number of arguments.
 * @argv: array of the arguments starting with the file's name.
 *
 * Return: always 0.
 */
int main(int argc, char *argv[])
{
	(void)argc;
	innerMain(argv);
	return (EXIT_SUCCESS);
}
/**
 * innerMain - the funciton that responsable for all in main function
 * the reason for making a sub-function is to handle freeing correctly
 * and for more readablity.
 * @argv: the arguments of the main program.
 */
void innerMain(char **argv)
{
	char *line;
	char **args;
	int st = 1, read = 0;
	size_t len = 0;
	char *temp_line;

	while (st)
	{
		line = NULL;
		read = getline(&line, &len, stdin);
		temp_line = line;
		if (read == -1)
		{
			if (feof(stdin))
			{
				free(temp_line);
			}
			else
			{
				perror("getline failed");
			}
			break;
		}
		while (*line == ' ')
		{
			line++;
		}
		if (*line == '\n')
		{
			if (line)
				free(temp_line);
			continue;
		}

		args = parser_func(line, argv);
		if (args == NULL)
		{
			free(line);
			break;
		}
		st = handleXcution(args, argv);
		free(temp_line);
		free(args[0]);
		free(args);
	}
}

/**
 * handlePath - handle the command if have no path
 * @arg: pointer to arg(the plain).
 */
char *handlePath(char **arg)
{
	char *path = getenv("PATH");
	char *fullPath = malloc(sizeof(char) * 1024);
	char *token;
	char *cpyPath = malloc(sizeof(char) * strlen(path) + 1);

	if (!cpyPath)
		return (NULL);

	strcpy(cpyPath, path);
	token = strtok(cpyPath, ":");
	while (token != NULL)
	{
		
		if (!fullPath)
			return (NULL);
		sprintf(fullPath, "%s/%s", token, arg[0]);

		if (access(fullPath, X_OK) == 0)
		{
			free(cpyPath);
			return (fullPath);
		}
		token = strtok(NULL, ":");
	}
	free(cpyPath);
	free(fullPath);
	return (NULL);
}