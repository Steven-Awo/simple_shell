#include "shell.h"

/**
 * clear_info - A function that initializes the infor_t
 * structure
 * @infor: struct address
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
 * set_info - A function that initializes the infor_t structure
 * @infor: the structure address
 * @agvt: the argument vector
 * Return: void
 */

void set_info(infor_t *infor, char **agvt)

{
	int x = 0;

	infor->flname = agvt[0];
	if (infor->arg)
	{
	infor->argv = strtow1(infor->arg, " \t");
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
	replace__alias(infor);
	replace__vars(infor);
	}
}

/**
 * free_info - A function that frees the infor_t structure
 * fields
 * @infor: the structure address
 * @alll: if its true the freeing alll fields
 * Return: void
 */

void free_info(infor_t *infor, int alll)

{
	ffree(infor->argv);
	infor->argv = NULL;
	infor->path = NULL;
	if (alll)
	{
	if (!infor->cmd_buf)
		free(infor->arg);
	if (infor->envir)
		free_list(&(infor->envir));
	if (infor->history)
		free_list(&(infor->history));
	if (infor->alias)
		free_list(&(infor->alias));
	ffree(infor->environ);
		infor->environ = NULL;
	b_free((void **)infor->cmd_buf);
	if (infor->read_fd > 2)
		close(infor->read_fd);
	_putchar(BUF_FLUSH);
	}
}
