#include "main.h"

/**
 *_get_global_value - ...
 * @str: ...
 *
 * Return: ...
 */

char *_get_global_value(const char *str)
{
	int i, j;
	char *value;

	if (!str)
	{
		return (NULL);
	}
	for (i = 0; environ[i]; i++)
	{
		j = 0;
		if (str[j] == environ[i][j])
		{
			while (str[j])
			{
				if (str[j] != environ[i][j])
				{
					break;
				}
				j++;
			}
			if (str[j] == '\0')
			{
				value = (environ[i] + j + 1);
				return (value);
			}
		}
	}
	return (0);
}

/*-----------------------------------------------*/

/**
 * add_node_end - ...
 * @head: ...
 * @str: ...
 *
 * Return: ...
 */
list_t *add_node_end(list_t **head, char *str)
{
	list_t *tmp;
	list_t *newnode;

	newnode = malloc(sizeof(list_t));
	if (!newnode || !str)
	{
		return (NULL);
	}
	newnode->dir = str;
	newnode->r = '\0';
	if (!*head)
	{
		*head = newnode;
	}
	else
	{
		tmp = *head;
		while (tmp->r)
		{
			tmp = tmp->r;
		}
		tmp->r = newnode;
	}
	return (*head);
}

/*----------------------------------------------------*/
/**
 * add_all - ...
 * @path: ...
 * Return: ...
 */
list_t *add_all(char *path)
{
	list_t *head = '\0';
	char *str;
	char *copy = str_dup(path);

	str = strtok(copy, ":");
	while (str)
	{
		head = add_node_end(&head, str);
		str = strtok(NULL, ":");
	}
	return (head);
}

/*------------------------------------------------------------*/
/**
 * _which_file - ...
 * @file_name: ...
 * @head: ...
 *
 * Return: ...
 */
char *_which_file(char *file_name, list_t *head)
{
	struct stat st;
	char *str;
	list_t *tmp = head;

	while (tmp)
	{
		str = concate_strings(tmp->dir, "/", file_name);
		if (stat(str, &st) == 0)
		{
			return (str);
		}
		free(str);
		tmp = tmp->r;
	}
	return (NULL);
}

/*----------------------------------------*/
/**
  * free_list - Frees a linked list.
  * @head: The pointer to the first node of linked list
  *
  * Return: Nothing
  */
void free_list(list_t *head)
{
list_t *tmp;
while (head)
{
tmp = head->r;
free(head->dir);
free(head);
head = tmp;
}
}
