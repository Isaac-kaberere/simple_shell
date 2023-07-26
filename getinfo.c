#include "shell.h"


void clear_info(info_t *half)
{
	half->arg = NULL;
	half->argv = NULL;
	half->path = NULL;
	half->argc = 0;
}

/**
 * set_info - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void set_info(info_t *half, char **av)
{
	int q = 0;

	half->fname = av[0];
	if (half->arg)
	{
		half->argv = strtow(half->arg, " \t");
		if (!half->argv)
		{
			half->argv = malloc(sizeof(char *) * 2);
			if (half->argv)
			{
				half->argv[0] = _strdup(half->arg);
				half->argv[1] = NULL;
			}
		}
		for (q = 0; half->argv && half->argv[q]; q++)
			;
		half->argc = q;

		replace_alias(half);
		replace_vars(half);
	}
}

/**
 * free_info - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_info(info_t *half, int all)
{
	ffree(half->argv);
	half->argv = NULL;
	half->path = NULL;
	if (all)
	{
		if (!half->cmd_buf)
			free(half->arg);
		if (half->env)
			free_list(&(half->env));
		if (half->history)
			free_list(&(half->history));
		if (half->alias)
			free_list(&(half->alias));
		ffree(half->environ);
			half->environ = NULL;
		bfree((void **)half->cmd_buf);
		if (half->readfd > 2)
			close(half->readfd);
		_putchar(BUF_FLUSH);
	}
}

