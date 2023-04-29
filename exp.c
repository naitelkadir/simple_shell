#include "main.h"
char *get_alias(command_life *data, char *name);
/**
 * expand_variables - ...
 * @cmd: ...
 * Return: ...
 */
void expand_variables(command_life *cmd)
{
	int i, j;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *new;
	
	if (cmd->line == NULL)
	{
		return;
	}
	add_at_end(line, cmd->line);
	for (i = 0; line[i]; i++)
	{
		if (line[i] == '#')
		{
			line[i--] = '\0';
		}
		else if (line[i] == '$' && line[i + 1] == '?')
		{
			line[i] = '\0';
			num_to_string(errno, expansion, 10);
			add_at_end(line, expansion);
			add_at_end(line, cmd->line + i + 2);
		}
		else if (line[i] == '$' && line[i + 1] == '$')
		{
			line[i] = '\0';
			num_to_string(getpid(), expansion, 10);
			add_at_end(line, expansion);
			add_at_end(line, cmd->line + i + 2);
		}
		else if (line[i] == '$' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
		{
			continue;
		}
		else if (line[i] == '$')
		{
			for (j = 1; line[i + j] && line[i + j] != ' '; j++)
			{
				expansion[j - 1] = line[i + j];
			}
			new = get_value(expansion, cmd);
			line[i] = '\0', expansion[0] = '\0';
			add_at_end(expansion, line + i + j);
			new ? add_at_end(line, new) : 1;
			add_at_end(line, expansion);
		}
	}
	if (!str_cmp(cmd->line, line, 0))
	{
		free(cmd->line);
		cmd->line = str_dup(line);
	}
}

/**
 * expand_alias - ...
 * cmd: ...
 * Return: ...
 */
void expand_alias(command_life *cmd)
{
	int i, j, c = 0;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'};
	char *new;

	if (cmd->line == NULL)
	{
		return;
	}
	add_at_end(line, cmd->line);
	for (i = 0; line[i]; i++)
	{
		for (j = 0; line[i + j] && line[i + j] != ' '; j++)
		{
			expansion[j] = line[i + j];
		}
		expansion[j] = '\0';
		new = get_alias(cmd, expansion);
		if (new)
		{
			expansion[0] = '\0';
			add_at_end(expansion, line + i + j);
			line[i] = '\0';
			add_at_end(line, new);
			line[str_len(line)] = '\0';
			add_at_end(line, expansion);
			c = 1;
		}
		break;
	}
	if (c)
	{
		free(cmd->line);
		cmd->line = str_dup(line);
	}
}

/**
 *add_at_end - ...
 * @b: ...
 * @s: ...
 * Return: ...
 */
int add_at_end(char *b, char *s)
{
	int len, i;
	
	len = str_len(b);
	for (i = 0; s[i]; i++)
	{
		b[len + i] = s[i];
	}
	b[len + i] = '\0';
	return (len + i);
}
