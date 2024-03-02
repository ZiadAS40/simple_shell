#include "main.h"

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
	return (0);
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

	while (st)
	{
		line = NULL;
		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			if (feof(stdin))
			{
				printf("\n");
				free(line);
			}
			else
			{
				perror("getline failed");
			}
			break;
		}
		args = parser_func(line);
		st = handleXcution(args, argv);
		free(line);
		free(args);
	}
}
