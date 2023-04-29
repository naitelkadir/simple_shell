#include "main.h"

int check_f(char *path);

/**
 * find_p - ...
 * @cmd: ...
 * Return: ...
 */
int find_p(command_life *cmd)
{
	int i = 0, c = 0;
	char **dir;
	
	if (!cmd->command_name)
	{
		return (2);
	}
	if (cmd->command_name[0] == '/' || cmd->command_name[0] == '.')
	{
		return (check_f(cmd->command_name));
	}
	free(cmd->tokens[0]);
	cmd->tokens[0] = concate_string(str_dup("/"), cmd->command_name);
	if (!cmd->tokens[0])
	{
		return (2);
	}
	dir = token_path(cmd);
	if (!dir || !dir[0])
	{
		errno = 127;
		return (127);
	}
	for (i = 0; dir[i]; i++)
	{
		dir[i] = concate_string(dir[i], cmd->tokens[0]);
		c = check_f(dir[i]);
		if (c == 0 || c == 126)
		{
			errno = 0;
			free(cmd->tokens[0]);
			cmd->tokens[0] = str_dup(dir[i]);
			free_array(dir);
			return (c);
		}
	}
	free(cmd->tokens[0]);
	cmd->tokens[0] = NULL;
	free_array(dir);
	return(c);
}

/**
 * token_path - ...
 * @cmd: ...
 * Return: ...
 */
char **token_path(command_life *cmd)
{
	int i = 0, c = 2;
	char **tokens = NULL;
	char *PATH;
	
	PATH = get_value("PATH", cmd);
	if ((PATH == NULL) || PATH[0] == '\0')
	{
		return (NULL);
	}
	PATH = str_dup(PATH);
	for (i = 0; PATH[i]; i++)
	{
		if (PATH[i] == ':')
		{
			c++;
		}
	}
	tokens = malloc(sizeof(char *) * c);
	i = 0;
	tokens[i] = str_dup(str_tok(PATH, ":"));
	while (tokens[i++])
	{
		tokens[i] = str_dup(str_tok(NULL, ":"));
	}
	free(PATH);
	return (tokens);
}

/**
 * check_f - ...
 * @path: ...
 * Return: ...
 */
int check_f(char *path)
{
	struct stat sb;
	
	if (stat(path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) || access(path, X_OK))
		{
			errno = 126;
			return (errno);
		}
		return (0);
	}
	errno = 127;
	return (127);
}
