#include "main.h"

/**
 * get_line - ...
 * @cmd: ...
 *
 * Return: ...
 */
int get_line(command_life *cmd)
{
	static char *array_cmd[10] = {NULL};
	static char array_op[10] = {'\0'};
	ssize_t read_t, i = 0;
	char b[BUFFER_SIZE] = {'\0'};
	
	if (!array_cmd[0] || (array_op[0] == '&' && errno != 0) || (array_op[0] == '|' && errno == 0))
	{
		for (i = 0; array_cmd[i]; i++)
		{
			free(array_cmd[i]);
			array_cmd[i] = NULL;
		}
		read_t = read(cmd->fd, b, BUFFER_SIZE - 1);
		if (read_t == 0)
		{
			return (-1);
		}
		i = 0;
		do {
			array_cmd[i] = str_dup(str_tok(i ? NULL : b, "\n;"));
			i = check_ops(array_cmd, i, array_op);
		} while (array_cmd[i++]);
	}
	cmd->line = array_cmd[0];
	for (i = 0; array_cmd[i]; i++)
	{
		array_cmd[i] = array_cmd[i + 1];
		array_op[i] = array_op[i + 1];
	}
	return(str_len(cmd->line));
}

/**
 * check_ops - ...
 * @n: ...
 * @array_cmd: ...
 * @array_op: ...
 *
 *Return: ...
 */
int check_ops(char *array_cmd[], int n, char array_op[])
{
	int j;
	char *new = NULL;
	
	for (j = 0; array_cmd[n] != NULL && array_cmd[n][j]; j++)
	{
		if (array_cmd [n][j] == '&' && array_cmd[n][j + 1] == '&')
		{
			new = array_cmd[n];
			array_cmd[n][j] = '\0';
			array_cmd[n] = str_dup(array_cmd[n]);
			array_cmd[n + 1] = str_dup(new + j + 2);
			n++;
			array_op[n] = '&';
			free(new);
			j = 0;
		}
		if (array_cmd[n][j] == '|' && array_cmd[n][j + 1] == '|')
		{
			new = array_cmd[n];
			array_cmd[n][j] = '\0';
			array_cmd[n] = str_dup(array_cmd[n]);
			array_cmd[n + 1] = str_dup(new + j + 2);
			n++;
			array_op[n] = '|';
			free(new);
			j = 0;
		}
	}
	return (n);
}
