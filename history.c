#include "shell.h"

/**
 * get_history_file - A function that gets the file history
 * @infor: A parameter structure
 * Return: the allocated string that contains the file history buffr
 */

char *get_history_file(infor_t *infor)
{
	char *buffr, *diry;

	diry = _getenv(infor, "HOME=");
	if (!diry)
	{
	return (NULL);
	}
	buffr = malloc(sizeof(char) * (_strlen(diry) + _strlen(HIST_FILE) + 2));
	if (!buffr)
	{
	return (NULL);
	}
	buffr[0] = 0;
	_strcpy(buffr, diry);
	_strcat(buffr, "/");
	_strcat(buffr, HIST_FILE);
	return (buffr);
}

/**
 * write_history - A function that creates a file, or appends
 * to any existing file
 * @infor: the parameter structure
 * Return: 1 (successful) or -1 (unsuccessful)
 */
int write_history(infor_t *infor)
{
	ssize_t fild;
	char *file_name = get_history_file(infor);
	list_t *nod = NULL;

	if (!file_name)
	{
	return (-1);
	}
	fild = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_name);
	if (fild == -1)
	{
	return (-1);
	}
	for (nod = infor->history; nod; nod = nod->nxt)
	{
	_putsfd(nod->strg, fild);
	_putfd('\n', fild);
	}
	_putfd(BUF_FLUSH, fild);
	close(fild);
	return (1);
}

/**
 * read_history - A function that reads the history from file
 * @infor: the parameter structure.
 * Return: hist_count (successful) or 0 (unsuccessful)
 */

int read_history(infor_t *infor)
{
	int x, last_f = 0, line_count = 0;
	ssize_t fild, rdlength, flsize = 0;
	struct stat stng;
	char *buffr = NULL, *file_name = get_history_file(infor);

	if (!file_name)
		return (0);
	fild = open(file_name, O_RDONLY);
	free(file_name);
	if (fild == -1)
		return (0);
	if (!fstat(fild, &stng))
		flsize = stng.st_size;
	if (flsize < 2)
		return (0);
	buffr = malloc(sizeof(char) * (flsize + 1));
	if (!buffr)
		return (0);
	rdlength = read(fild, buffr, flsize);
	buffr[flsize] = 0;
	if (rdlength <= 0)
		return (free(buffr), 0);
	close(fild);
	for (x = 0; x < flsize; x++)
		if (buffr[x] == '\n')
		{
		buffr[x] = 0;
		build_history_list(infor, buffr + last_f, line_count++);
		last_f = x + 1;
		}
	if (last_f != x)
		build_history_list(infor, buffr + last_f, line_count++);
	free(buffr);
	infor->hist_count = line_count;
	while (infor->hist_count-- >= HIST_MAX)
		delete_node_at_index(&(infor->history), 0);
	renumber_history(infor);
	return (infor->hist_count);
}

/**
 * build_history_list - A function that adds an entry to a history
 * in the linked list
 * @infor: the structure that contains potential arguments.
 * Used to maintain constant function prototype.
 * @buffr: the buffer
 * @line_count: the history number of line_count, hist_count
 * Return: 0 (Always)
 */

int build_history_list(infor_t *infor, char *buffr, int line_count)

{
	list_t *nod = NULL;

	if (infor->history)
	{
	nod = infor->history;
	}
	add_node_end(&nod, buffr, line_count);
	if (!infor->history)
	{
	infor->history = nod;
	}
	return (0);
}

/**
 * renumber_history - A function that renumbers the history
 * of the linked list after changes
 * @infor:the structure that contains potential arguments.
 * Used to maintain constant function prototype
 * Return: the new hist_count (successful)
 */

int renumber_history(infor_t *infor)

{
	list_t *nod = infor->history;
	int x = 0;

	while (nod)
	{
	nod->numb = x++;
	nod = nod->nxt;
	}
	return (infor->hist_count = x);
}
