#include "shell.h"

/**
 * get_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history_file(info_t *half)
{
	char *baf, *dar;

	dar = _getenv(half, "HOME=");
	if (!dar)
		return (NULL);
	baf = malloc(sizeof(char) * (_strlen(dar) + _strlen(HIST_FILE) + 2));
	if (!baf)
		return (NULL);
	baf[0] = 0;
	_strcpy(baf, dar);
	_strcat(baf, "/");
	_strcat(baf, HIST_FILE);
	return (baf);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *half)
{
	ssize_t fd;
	char *filename = get_history_file(half);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = half->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *half)
{
	int k, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *baf = NULL, *filename = get_history_file(half);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	baf = malloc(sizeof(char) * (fsize + 1));
	if (!baf)
		return (0);
	rdlen = read(fd, baf, fsize);
	baf[fsize] = 0;
	if (rdlen <= 0)
		return (free(baf), 0);
	close(fd);
	for (k = 0; k < fsize; k++)
		if (baf[k] == '\n')
		{
			baf[k] = 0;
			build_history_list(half, baf + last, linecount++);
			last = k + 1;
		}
	if (last != k)
		build_history_list(half, baf + last, linecount++);
	free(baf);
	half->histcount = linecount;
	while (half->histcount-- >= HIST_MAX)
		delete_node_at_index(&(half->history), 0);
	renumber_history(half);
	return (half->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *half, char *baf, int linecount)
{
	list_t *node = NULL;

	if (half->history)
		node = half->history;
	add_node_end(&node, baf, linecount);

	if (!half->history)
		half->history = node;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *half)
{
	list_t *node = half->history;
	int k = 0;

	while (node)
	{
		node->num = k++;
		node = node->next;
	}
	return (half->histcount = k);
}

