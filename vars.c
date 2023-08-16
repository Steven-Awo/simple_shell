#include "shell.h"

/**
 * is_chainn - This function test if current char in bufer is a chain delimeter
 * @infor: This is the parameter struct
 * @bbuf: This is the char buffer
 * @p: This is address of current position in bbuf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chainn(infor_t *infor, char *bbuf, size_t *p)
{
	size_t w = *p;

	if (bbuf[w] == '|' && bbuf[w + 1] == '|')
	{
		bbuf[w] = 0;
		w++;
		infor->cmd_buf_type = CMD_OR;
	}
	else if (bbuf[w] == '&' && bbuf[w + 1] == '&')
	{
		bbuf[w] = 0;
		w++;
		infor->cmd_buf_type = CMD_AND;
	}
	else if (bbuf[w] == ';') /* found end of this command */
	{
		bbuf[w] = 0; /* replace semicolon with null */
		infor->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = w;
	return (1);
}

/**
 * check_chainn - If we should continue chaining based on last status
 * @infor: This is the parameter struct
 * @bbuf: This is the char buffer
 * @p: This is address of current position: This is starting position in bbuf
 * @lent: This is the length of bbuf
 *
 * Return: Void
 */
void check_chainn(infor_t *infor, char *bbuf, size_t *p, size_t a, size_t lent)
{
	size_t w = *p;

	if (infor->cmd_buf_type == CMD_AND)
	{
		if (infor->status)
		{
			bbuf[a] = 0;
			w = lent;
}
	}
	if (infor->cmd_buf_type == CMD_OR)
	{
		if (!infor->status)
		{
			bbuf[a] = 0;
			w = lent;
}
	}

	*p = w;
}

/**
 * rreplace_aliass - This function replaces an aliases in the tokenized string
 * @infor: This is the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rreplace_aliass(infor_t *infor)
{
	int a;
	list_t *node;
	char *p;

	for (a = 0; a < 10; a++)
	{
		node = node_starts_with(infor->alias, infor->argv[0], '=');
		if (!node)
			return (0);
		free(infor->argv[0]);
		p = _strchr(node->strg, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		infor->argv[0] = p;
	}
	return (1);
}

/**
 * rreplace_varrs - This function replaces vars in the tokenized string
 * @infor: This is the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rreplace_varrs(infor_t *infor)
{
	int a = 0;
	list_t *node;

	for (a = 0; infor->argv[a]; a++)
	{
		if (infor->argv[a][0] != '$' || !infor->argv[a][1])
			continue;

		if (!_strcmp(infor->argv[a], "$?"))
		{
			rreplace_strring(&(infor->argv[a]),
					_strdup(convert_number(infor->status, 10, 0)));
			continue;
		}
		if (!_strcmp(infor->argv[a], "$$"))
		{
			rreplace_strring(&(infor->argv[a]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(infor->envir, &infor->argv[a][1], '=');
		if (node)
		{
			rreplace_strring(&(infor->argv[a]),
					_strdup(_strchr(node->strg, '=') + 1));
			continue;
		}
		rreplace_strring(&infor->argv[a], _strdup(""));

	}
	return (0);
}

/**
 * rreplace_strring - This function replaces string
 * @oold: This is the address of oold string
 * @neww: This is neww string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rreplace_strring(char **oold, char *neww)
{
	free(*oold);
	*oold = neww;
	return (1);
}
