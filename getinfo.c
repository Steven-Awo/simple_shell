#include "shell.h"

/**
 * clear_info - A function that initializes the info_t structure
 * @info: struct address
 * Return: void
 */

void clear_info(infor_t *infor)
{
	infor->arg = NULL;
	infor->argv = NULL;
	infor->path = NULL;
	infor->argc = 0;
}

/**
 * set_infor - A function that initializes the infor_t structure
 * @infor: the structure address
 * @av: argument vector
 * Return: void
 */

void set_infor(infor_t *infor, char **av)
{
	int x = 0;

	infor->flname = av[0];
	if (infor->arg)
	{
	infor->argv = strtow(infor->arg, " \t");
	if (!infor->argv)
	{
	infor->argv = malloc(sizeof(char *) * 2);
	if (infor->argv)
	{
	infor->argv[0] = _strdup(infor->arg);
	infor->argv[1] = NULL;
	}
	}
	for (x = 0; infor->argv && infor->argv[x]; x++)
		;
	infor->argc = x;
	replace_alias(infor);
	replace_vars(infor);
	}
}

/**
 * free_infor - A function that frees the infor_t structure fields
 * @infor: the structure address
 * @all: is true if freeing all fields
 * Return: void
 */

void free_infor(infor_t *infor, int all)
{
	ffree(infor->argv);
	infor->argv = NULL;
	infor->path = NULL;
	if (all)
	{
	if (!infor->cmd_buf)
	{
	free(infor->arg);
	}
	if (infor->envir)
	{
	free_list(&(infor->envir));
	}
	if (infor->history)
	{
	free_list(&(infor->history));
	}
	if (infor->alias)
	{
	free_list(&(infor->alias));
	}
	free(infor->environ);
	infor->environ = NULL;
	free((void **)infor->cmd_buf);
	if (infor->read_fd > 2)
		close(infor->read_fd);
	_putchar(BUF_FLUSH);
	}
}
