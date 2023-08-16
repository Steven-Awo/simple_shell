#include "shell.h"

/**
 * list_lenz - This function determines length of linked list
 * @h: This is the pointer to first nodee
 *
 * Return: size of list
 */
size_t list_lenz(const list_t *h)
{
	size_t b = 0;

	while (h)
	{
	h = h->nxt;
	b++;
	}
	return (b);
}

/**
 * list_to_stringgs- This function returns an arrayof strings of the list->strg
 * @headdz: This is the pointer to first nodee
 *
 * Return: array of strgings
 */
char **list_to_stringgs(list_t *headdz)
{
	list_t *nodee = headdz;
	size_t b = list_lenz(headdz), j;
	char **strgs;
	char *strg;

	if (!headdz || !(b))
	return (NULL);
	strgs = malloc(sizeof(char *) * (b + 1));
	if (!strgs)
		return (NULL);
	for (b = 0; nodee; nodee = nodee->nxt, b++)
	{
		strg = malloc(_strlen(nodee->strg) + 1);
		if (!strg)
		{
			for (j = 0; j < b; j++)
				free(strgs[j]);
			free(strgs);
			return (NULL);
		}

		strg = _strcpy(strg, nodee->strg);
		strgs[b] = strg;
	}
	strgs[b] = NULL;
	return (strgs);
}


/**
 * print_listtz - This function prints all elements of a list_t linked list
 * @h: This is the pointer to first nodee
 *
 * Return: size of list
 */
size_t print_listtz(const list_t *h)
{
	size_t b = 0;

	while (h)
	{
	_puts(convert_number(h->numb, 10, 0));
	_putchar(':');
		_putchar(' ');
		_puts(h->strg ? h->strg : "(nil)");
		_puts("\n");
		h = h->nxt;
		b++;
	}
	return (b);
}

/**
 * nodeee_starrts_witth - This function returns node strging starts with prefix
 * @nodee: This is the pointer to list headdz
 * @prefixx: This is the strging to match
 * @c: This is the nxt character after prefix to match
 *
 * Return: match node or null
 */
list_t *nodeee_starrts_witth(list_t *nodee, char *prefixx, char c)
{
	char *p = NULL;

	while (nodee)
	{
		p = starts_with(nodee->strg, prefixx);
		if (p && ((c == -1) || (*p == c)))
			return (nodee);
		nodee = nodee->nxt;
	}
	return (NULL);
}

/**
 * get_nodee_indexx - This function gets the index of a nodee
 * @headdz: This is the pointer to list headdz
 * @nodee: This is the pointer to the nodee
 *
 * Return: index of nodee or -1
 */
ssize_t get_nodee_indexx(list_t *headdz, list_t *nodee)
{
	size_t b = 0;

	while (headdz)
	{
	if (headdz == nodee)
	return (b);
	headdz = headdz->nxt;
	b++;
	}
	return (-1);
}
