#include "shell.h"

/**
 * _myenv - Prints the current environment variables.
 * @info: A structure containing potential arguments. Used to maintain
 *        a consistent function prototype.
 *
 * This function is responsible for printing the current environment variables
 * associated with the shell process. The environment variables contain various
 * settings and information that can be accessed by the shell and other programs.
 * 
 * The @info argument is used to maintain a consistent function prototype, but it
 * is not utilized in this implementation.
 *
 * Return: Always 0
 */

int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _myenv - Prints the current environment variables.
 * @info: A structure containing potential arguments. Used to maintain
 *        a consistent function prototype.
 *
 * This function is responsible for printing the current environment variables
 * associated with the shell process. The environment variables contain various
 * settings and information that can be accessed by the shell and other programs.
 * 
 * The @info argument is used to maintain a consistent function prototype, but it
 * is not utilized in this implementation.
 *
 * Return: Always 0
 */

char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - Populates the environment linked list.
 * @info: A structure containing potential arguments. Used to maintain
 *        a consistent function prototype.
 *
 * This function is responsible for populating a linked list with the current
 * environment variables. Environment variables store various system and user
 * information that can be accessed by programs. The function takes the @info
 * argument for maintaining a consistent function prototype, but it is not 
 * utilized in this implementation.
 * 
 * The linked list will hold the environment variables, where each node of the
 * list will store the name and value of an environment variable.
 *
 * Return: Always 0
 */

int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}

