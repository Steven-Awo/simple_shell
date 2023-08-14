#include "shell.h"

/**
 * get_environ - A function that returns the array of string copy
 * of our environment.
 * @infor: the structure that contains potential arguments.
 * Used to maintain constant function prototype.
 * Return: 0 (Always)
 */

char **get_environ(infor_t *infor)

{
	if (!infor->environ || infor->envir_changed)
	{
	infor->environ = list_to_strings(infor->envir);
	infor->envir_changed = 0;
	}
	return (infor->environ);
}

/**
 * _unsetenv - A function that removes an envir variable
 * @infor: the structure that contains potential arguments.
 * Used to maintain constant function prototype.
 * @vari: the environment vari of strings property
 *  Return: 1 (delete) or 0 (otherwise)
 */

int _unsetenv(infor_t *infor, char *vari)

{
	list_t *nod = infor->envir;
	size_t x = 0;
	char *y;

	if (!nod || !vari)
	{
	return (0);
	}
	while (nod)
	{
	y = starts_with(nod->strg, vari);
	if (y && *y == '=')
	{
	infor->envir_changed = delete_node_at_index(&(infor->envir), x);
	x = 0;
	nod = infor->envir;
	continue;
	}
	nod = nod->nxt;
	x++;
	}
	return (infor->envir_changed);
}

/**
 * _setenv - A function that initializes a new environ variable,
 * or modify any existing one
 * @infor: the structure that contains potential arguments.
 * Used to maintain constant function prototype.
 * @vari: the string envir vari property
 * @val: the string env vari val
 *  Return: 0 (Always)
 */

int _setenv(infor_t *infor, char *vari, char *val)
{
	char *buf = NULL;
	list_t *nod;
	char *y;

	if (!vari || !val)
	{
	return (0);
	}
	buf = malloc(_strlen(vari) + _strlen(val) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, vari);
	_strcat(buf, "=");
	_strcat(buf, val);
	nod = infor->envir;
	while (nod)
	{
	y = starts_with(nod->strg, vari);
	if (y && *y == '=')
	{
	free(nod->strg);
	nod->strg = buf;
	infor->envir_changed = 1;
	return (0);
	}
	nod = nod->nxt;
	}
	add_node_end(&(infor->envir), buf, 0);
	free(buf);
	infor->envir_changed = 1;
	return (0);
}
