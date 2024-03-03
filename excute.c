#include "main.h"

/**
 * handleXcution - handle the process of excution on the main shell.
 * @args: an array of string (Commands) to excute.
 * @argv: the argument of the main program.
 * Return: 1
 */

int handleXcution(char **args, char **argv)
{
	pid_t pid;
	int proc_status;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror(argv[0]);
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror(argv[0]);
	}
	else
	{
		do
		{
			waitpid(pid, &proc_status, WUNTRACED);
		} while (!WIFEXITED(proc_status) && !WIFSIGNALED(proc_status));
	}

	return (1);
}
