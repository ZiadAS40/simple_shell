#include "main.h"
/**
 * _strtok - tokenize a stirng
 * @line: the string
 * @sep: the separator
 * Return: a token
 */
char *_strtok(char *line, char sep)
{
	static char *local_buffer, *temp_buffer;
	int i = 0, result_size = 120;
	char *result = malloc(sizeof(char) * result_size);

	if (!result)
	{
		free(result);
		free(local_buffer);
		return (NULL);
	}
	if (line == NULL && local_buffer == NULL)
	{
		free(result);
		return (NULL);
	}
	if (line != NULL)
	{
		local_buffer = malloc(strlen(line) + 1);
		if (local_buffer == NULL)
		{
			free(result);
			return (NULL);
		}
		temp_buffer = local_buffer;
		strcpy(local_buffer, line);
	}
	if (*local_buffer == '\0')
	{
		free(result);
		free(temp_buffer);
		return (NULL);
	}
	while (*local_buffer == ' ')
		local_buffer++;
	while (*local_buffer != '\0' && *local_buffer != sep)
	{
		if (i >= result_size - 1)
		{
			custom_realloc(&result, &result_size);
			if (!result)
			{
				free(temp_buffer);
				return (NULL);
			}
		}
		result[i++] = *local_buffer++;
	}
	result[i] = '\0';
	if (*local_buffer == sep)
		local_buffer++;
	return (result);
}
