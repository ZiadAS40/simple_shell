#include "main.h"

/**
 * _getline - work like the plain one.
 * @lineptr: a pointer to the line.
 * @len: a pointer to the length of the line.
 * @stream: a file stream pointer.
 * Return: the number of reader characters on Success
 * -1 if fails
 */

ssize_t _getline(char **lineptr, size_t *len, FILE *stream)
{
	static ssize_t n;
	ssize_t k;
	char c = 'n', *buffer;
	int r, buffer_size = 120;

	buffer = malloc(sizeof(char) * buffer_size);
	if (buffer == NULL)
		return (-1);

	if (n == 0)
		fflush(stream);
	else
		return (-1);
	n = 0;
	while (c != '\n')
	{
		r = read(STDOUT_FILENO, &c, 1);
		if (r == -1 || (n == 0 && r == 0))
		{
			free(buffer);
			return (-1);
		}
		if (n != 0 && r == 0)
		{
			n++;
			break;
		}
		if (n >= 120)
		{
			custom_realloc(&buffer, &buffer_size);
		}
		buffer[n] = c;
		n++;
	}
	buffer[n] = '\0';
	*lineptr = buffer;
	*len = buffer_size;
	k = n;
	n = 0;
	return (k);
}

/**
 * custom_realloc - just for saving some space for bttey :)
 * @buffer: the string that should realloc.
 * @buffer_size: a pointer to the buffer_size.
 */
void custom_realloc(char **buffer, int *buffer_size)
{
	char *temp_buffer;

	*buffer_size += 120;
	temp_buffer = realloc(*buffer, (size_t)(*buffer_size));
	if (temp_buffer == NULL)
	{
		free(temp_buffer);
		exit(EXIT_FAILURE);
	}
	*buffer = temp_buffer;
}
