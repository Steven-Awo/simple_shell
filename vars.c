#include "shell.h"

/**
 * is__chain - A function that test to check if current the char
 * in the buffer is a chain delimeter
 * @infor: the parameter structure in shell.h
 * @bufr: the buffer for the char
 * @c_p: the current position address in buff function
 * Return: 1 (chain delimeter) or 0 (otherwise)
 */
int is__chain(infor_t *infor, char *bufr, size_t *c_p)
{
	size_t y = *c_p;

	if (bufr[y] == '|' && bufr[y + 1] == '|')
	{
	bufr[y] = 0;
	y++;
	infor->cmd_buf_type = CMD_OR;
	}
	else if (bufr[y] == '&' && bufr[y + 1] == '&')
	{
	bufr[y] = 0;
	y++;
	infor->cmd_buf_type = CMD_AND;
	}
	else if (bufr[y] == ';') /* found end of this command */
	{
	bufr[y] = 0; /* replace semicolon ':' with null */
	infor->cmd_buf_type = CMD_CHAIN;
	}
	else
	{
	return (0);
	}
	*c_p = y;
	return (1);
}

/**
 * check__chain - A function that checks if we could continue the chaining
 * that is based on last status
 * @infor: the parameter structure in shelll.h
 * @buf: the char buffer
 * @c_p: the current position address in bufr
 * @x: the beginning or starting position in the bufr
 * @len: the bufr lenght
 * Return: void
 */

void check__chain(infor_t *infor, char *buf, size_t *c_p, size_t x, size_t len)

{
	size_t y = *c_p;

	if (infor->cmd_buf_type == CMD_AND)
	{
	if (infor->status)
	{
	buf[x] = 0;
	y = len;
	}
	}
	if (infor->cmd_buf_type == CMD_OR)
	{
	if (!infor->status)
	{
	buf[x] = 0;
	y = len;
	}
	}
	*c_p = y;
}

/**
 * replace__alias - A function that replaces an aliases in
 * the string that is tokenized
 * @infor: the parameter structure in shell.h
 * Return: 1 (when replaced) or 0 (fail or otherwise)
 */
int replace__alias(infor_t *infor)
{
	int x;
	list_t *nod;
	char *c_p;

	for (x = 0; x < 10; x++)
	{
	nod = node_starts_with(infor->alias, infor->argv[0], '=');
	if (!nod)
	{
	return (0);
	}
	free(infor->argv[0]);
	c_p = _strchr(nod->strg, '=');
	if (!c_p)
	{
	return (0);
	}
	c_p = _strdup(c_p + 1);
	if (!c_p)
	{
	return (0);
	}
	infor->argv[0] = c_p;
	}
	return (1);
}

/**
 * replace__vars - A function that replaces the vars in
 * the string that is tokenized
 * @infor: the parameter structure shell.h
 * Return: 1 (if when replaced) or 0 (fail or otherwise)
 */
int replace__vars(infor_t *infor)
{
	int x = 0;
	list_t *nod;

	for (x = 0; infor->argv[x]; x++)
	{
	if (infor->argv[x][0] != '$' || !infor->argv[x][1])
	{
	continue;
	}
	if (!_strcmp(infor->argv[x], "$?"))
	{
	replace__string(&(infor->argv[x]),
			_strdup(convert_number(infor->status, 10, 0)));
	continue;
	}
	if (!_strcmp(infor->argv[x], "$$"))
	{
	replace__string(&(infor->argv[x]),
			_strdup(convert_number(getpid(), 10, 0)));
	continue;
	}
	nod = node_starts_with(infor->envir, &infor->argv[x][1], '=');
	if (nod)
	{
	replace__string(&(infor->argv[x]),
			_strdup(_strchr(nod->strg, '=') + 1));
	continue;
	}
	replace__string(&infor->argv[x], _strdup(""));
	}
	return (0);
}

/**
 * replace__string - A function that replaces string(s)
 * @old_s_a: the old_s_a string's address
 * @new_s_a: the new_s_a string's address
 * Return: 1 (if when replaced) or 0 (otherwise)
 */

int replace__string(char **old_s_a, char *new_s_a)

{
	free(*old_s_a);
	*old_s_a = new_s_a;
	return (1);
}
