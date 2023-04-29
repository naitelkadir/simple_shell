#include "main.h"

/**
 * token_it - ...
 * cmd: ...
 * Return: ...
 */
void token_it(command_life *cmd)
{
	int i, j, c = 2, len;
	char *delim = " \t";
	
	len = str_len(cmd->line);
	if (len)
	{
		if (cmd->line[len - 1] == '\n')
		{
			cmd->line[len - 1] = '\0';
		}
	}
	for (i = 0; cmd->line[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (cmd->line[i] == delim[j])
			{
				c++;
			}
		}
	}
	cmd->tokens = malloc(c * sizeof(char *));
	if (cmd->tokens == NULL)
	{
		perror(cmd->command_name);
		exit(errno);
	}
	i = 0;
	cmd->tokens[i] = str_dup(str_tok(cmd->line, delim));
	cmd->command_name = str_dup(cmd->tokens[0]);
	while (cmd->tokens[i++])
	{
		cmd->tokens[i] = str_dup(str_tok(NULL, delim));
	}
}
