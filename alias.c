#include "main.h"

char *get_alias(command_life *data, char *name);

int print_alias(command_life *data, char *alias)
{
	int i, j, alias_length;
	char buffer[250] = {'\0'};

	if (data->alias_t)
	{
		alias_length = str_len(alias);
		for (i = 0; data->alias_t[i]; i++)
		{
			if (!alias || (str_cmp(data->alias_t[i], alias, alias_length)
				&&	data->alias_t[i][alias_length] == '='))
			{
				for (j = 0; data->alias_t[i][j]; j++)
				{
					buffer[j] = data->alias_t[i][j];
					if (data->alias_t[i][j] == '=')
						break;
				}
				buffer[j + 1] = '\0';
				add_at_end(buffer, "'");
				add_at_end(buffer, data->alias_t[i] + j + 1);
				add_at_end(buffer, "'\n");
				_puts(buffer);
			}
		}
	}

	return (0);
}

/**
 * get_alias - add, remove or show aliases
 * @data: struct for the program's data
 * @name: name of the requested alias.
 * Return: zero if sucess, or other number if its declared in the arguments
 */
char *get_alias(command_life *data, char *name)
{
	int i, alias_length;

	/* validate the arguments */
	if (name == NULL || data->alias_t == NULL)
		return (NULL);

	alias_length = str_len(name);

	for (i = 0; data->alias_t[i]; i++)
	{/* Iterates through the environ and check for coincidence of the varname */
		if (str_cmp(name, data->alias_t[i], alias_length) &&
			data->alias_t[i][alias_length] == '=')
		{/* returns the value of the key NAME=  when find it */
			return (data->alias_t[i] + alias_length + 1);
		}
	}
	/* returns NULL if did not find it */
	return (NULL);

}

/**
 * set_alias - add, or override alias
 * @alias_string: alias to be seted in the form (name='value')
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int set_alias(char *alias_string, command_life *data)
{
	int i, j;
	char buffer[250] = {'0'}, *temp = NULL;

	/* validate the arguments */
	if (alias_string == NULL ||  data->alias_t == NULL)
		return (1);
	/* Iterates alias to find = char */
	for (i = 0; alias_string[i]; i++)
		if (alias_string[i] != '=')
			buffer[i] = alias_string[i];
		else
		{/* search if the value of the alias is another alias */
			temp = get_alias(data, alias_string + i + 1);
			break;
		}

	/* Iterates through the alias list and check for coincidence of the varname */
	for (j = 0; data->alias_t[j]; j++)
		if (str_cmp(buffer, data->alias_t[j], i) &&
			data->alias_t[j][i] == '=')
		{/* if the alias alredy exist */
			free(data->alias_t[j]);
			break;
		}

	/* add the alias */
	if (temp)
	{/* if the alias already exist */
		add_at_end(buffer, "=");
		add_at_end(buffer, temp);
		data->alias_t[j] = str_dup(buffer);
	}
	else /* if the alias does not exist */
		data->alias_t[j] = str_dup(alias_string);
	return (0);
}
