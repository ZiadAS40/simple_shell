#include "main.h"

/**
 * handleExit - handle the exit built in.
 * @arg: a pointer to arg[the array of arguments].
 */
void handleExit(char ***arg)
{

	char *message = "exit\nbash: exit : too many arguments\n";

	if (arg[1] == NULL)
		exit(EXIT_SUCCESS);
	if (arg[1] != NULL && arg[2] == NULL)
	{
		exit(atoi((*arg)[2]));
	}

	write(STDERR_FILENO, message, strlen(message));
}
