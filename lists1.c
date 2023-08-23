#include "shell.h"

/**
 * list_len - A function that determines linked list length
 * @hed: The pointer to the first nod
 * Return: x the size of the list
 */

size_t list_len(const list_t *hed)

{
	size_t x = 0;

	while (hed)
	{
	hed = hed->nxt;
	x++;
	}
	return (x);
}

/**
 * list_to_strings - the fuction that returns an array of strgs of
 * the list ->strng
 * @hed: the pointer to the first nod
 * Return: the array of strgs(strgs)
 */

char **list_to_strings(list_t *hed)
{
	list_t *nod = hed;
	size_t x = list_len(hed), y;
	char **strgs;
	char *strng;

	if (!hed || !x)
		return (NULL);
	strgs = malloc(sizeof(char *) * (x + 1));
	if (!strgs)
	{
	return (NULL);
	}
	for (x = 0; nod; nod = nod->nxt, x++)
	{
	strng = malloc(_strlen(nod->strg) + 1);
	if (!strng)
	{
	for (y = 0; y < x; y++)
		free(strgs[y]);
	free(strgs);
	return (NULL);
	}
	strng = _strcpy(strng, nod->strg);
	strgs[x] = strng;
	}
	strgs[x] = NULL;
	return (strgs);
}


/**
 * print_list - A function that prints all the elements of a
 * list_t linked list out.
 * @hed: the pointer to the first nod
 * Return: x (successfull) list size
 */
size_t print_list(const list_t *hed)
{
	size_t x = 0;

	while (hed)
	{
	_puts(convert_number(hed->numb, 10, 0));
	_putchar(':');
	_putchar(' ');
	_puts(hed->strg ? hed->strg : "(nil)");
	_puts("\n");
	hed = hed->nxt;
	x++;
	}
	return (x);
}

/**
 * node_starts_with - returns nod whose string starts with prefx
 * @nod: pointer to list hed
 * @prefx: string to match
 * @g: the next character after prefx to match
 * Return: match nod or null
 */

list_t *node_starts_with(list_t *nod, char *prefx, char g)

{
	char *p = NULL;

	while (nod)
	{
	p = starts_with(nod->strg, prefx);
	if (p && ((g == -1) || (*p == g)))
	{
	return (nod);
	}
	nod = nod->nxt;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a nod
 * @hed: the pointer to the list hed
 * @nod: the pointer to the nod
 * Return: x (successfull) nod index or -1 (unsuccessful)
 */

ssize_t get_node_index(list_t *hed, list_t *nod)

{
	size_t x = 0;

	while (hed)
	{
	if (hed == nod)
	{
	return (x);
	}
	hed = hed->nxt;
	x++;
	}
	return (-1);
}
