#include "shell.h"

/**
 * _myenv - A function that prints out the current environment
 * @infor: the structure that contains potential arguments.
 * Used to maintain constant function prototype.
 * Return: 0 (Always)
 */

int _myenv(infor_t *infor)
{
	print_list_str(infor->envir);
	return (0);
}

/**
 * _getenv - A function that gets the value of variable of the env
 * @infor: the structure that contains potential arguments.
 * Used to maintain constant function prototype.
 * @name: the variable name of the environment
 * Return: value
 */

char *_getenv(infor_t *infor, const char *name)

{
	list_t *nod = infor->envir;
	char *ge;

	while (nod)
	{
	ge = starts_with(nod->strg, name);
	if (ge && *ge)
	{
	return (ge);
	}
	nod = nod->nxt;
	}
	return (NULL);
}

/**
 * _mysetenv - A function that initialize a new environ variable,
 * or modify any existing one
 * @infor: the structure that contains potential arguments.
 * Used to maintain constant function prototype.
 *  Return: 0 (Always)
 */

int _mysetenv(infor_t *infor)

{
	if (_setenv(infor, infor->argv[1], infor->argv[2]))
	{
	return (0);
	}
	if (infor->argc != 3)
	{
	_eputs("Incorrect number of arguements\n");
	return (1);
	}
	return (1);
}

/**
 * _myunsetenv - A function that removes an environ variable
 * @infor: the structure that contains potential arguments.
 * Used to maintain constant function prototype.
 * Return: 0 (Always)
 */

int _myunsetenv(infor_t *infor)

{
	int w;

	if (infor->argc == 1)
	{
	_eputs("Too few arguements.\n");
	return (1);
	}
	for (w = 1; w <= infor->argc; w++)
	{
	_unsetenv(infor, infor->argv[w]);
	}
	return (0);
}

/**
 * populate_env_list - A function that populates the env linked list
 * @infor: the structure that contains potential arguments.
 * Used to maintain constant function prototype.
 * Return: 0 (Always)
 */

int populate_env_list(infor_t *infor)

{
	list_t *nod = NULL;
	size_t a;

	for (a = 0; environ[a]; a++)
	{
	add_node_end(&nod, environ[a], 0);
	}
	infor->envir = nod;
	return (0);
}
