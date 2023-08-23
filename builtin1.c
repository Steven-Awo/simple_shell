#include "shell.h"

/**
 * _myhistory - A fuction that displays one command by line,
 * history list, preceded with line numbers, starting at 0.
 * @infor: the structure that contains potential arguments.
 * Used to maintain constant function prototype.
 *  Return: 0 (Always)
 */

int _myhistory(infor_t *infor)
{
	print_list(infor->history);
	return (0);
}

/**
 * unset_alias - A function that sets alias to as string
 * @infor: the parameter structure
 * @strg: the string for alias
 * Return: 0 (success) or 1 (error)
 */

int unset_alias(infor_t *infor, char *strg)
{
	char *as, b;
	int retn;

	as = _strchr(strg, '=');
	if (!as)
	{
	return (1);
	}
	b = *as;
	*as = 0;
	retn = delete_node_at_index(&(infor->alias),
			get_node_index(infor->alias,
			node_starts_with(infor->alias, strg, -1)));
	*as = b;
	return (retn);
}

/**
 * set_alias - A function that sets alias to as string
 * @infor: the parameter structure
 * @strg: the string alias
 * Return: 0 (successful) or 1 (error)
 */

int set_alias(infor_t *infor, char *strg)
{
	char *as;

	as = _strchr(strg, '=');
	if (!as)
	{
	return (1);
	}
	if (!*++as)
	{
	return (unset_alias(infor, strg));
	}
	unset_alias(infor, strg);
	return (add_node_end(&(infor->alias), strg, 0) == NULL);
}

/**
 * print_alias - a function prints an alias string
 * @nod: the alias node
 * Return: 0 (successful) or 1 (error)
 */

int print_alias(list_t *nod)

{
	char *ps = NULL, *as = NULL;

	if (nod)
	{
	ps = _strchr(nod->strg, '=');
	for (as = nod->strg; as <= ps; as++)
	_putchar(*as);
	_putchar('\'');
	_puts(as + 1);
	_puts("'\n");
	return (0);
	}
	return (1);
}

/**
 * _myalias - A function that mimics the alias builtin
 * (man alias)
 * @infor: the structure that contains potential arguments.
 * Used to maintain constant function prototype..
 * Return: 0 (always)
 */

int _myalias(infor_t *infor)
{
	int i = 0;
	char *as = NULL;
	list_t *nod = NULL;

	if (infor->argc == 1)
	{
	nod = infor->alias;
	while (nod)
	{
	print_alias(nod);
	nod = nod->nxt;
	}
	return (0);
	}
	for (i = 1; infor->argv[i]; i++)
	{
	as = _strchr(infor->argv[i], '=');
	if (as)
	{
	set_alias(infor, infor->argv[i]);
	}
	else
	{
	print_alias(node_starts_with(infor->alias, infor->argv[i], '='));
	}
	}
	return (0);
}
