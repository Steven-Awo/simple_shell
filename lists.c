#include "shell.h"

/**
 * add_node - A function that adds a nod to the start of the list
 * @Head: the Head nod address of pointer
 * @strg: the strg field of nod
 * @numb: nod indx used by history
 * Return: new_headthe size of the list
 */

list_t *add_node(list_t **Head, const char *strg, int numb)

{
	list_t *newhead;

	if (!Head)
	{
	return (NULL);
	}
	newhead = malloc(sizeof(list_t));
	if (!newhead)
	{
	return (NULL);
	}
	_memset((void *)newhead, 0, sizeof(list_t));
	newhead->numb = numb;
	if (strg)
	{
	newhead->strg = _strdup(strg);
	if (!newhead->strg)
	{
	free(newhead);
	return (NULL);
	}
	}
	newhead->nxt = *Head;
	*Head = newhead;
	return (newhead);
}

/**
 * add_node_end - A function that adds a nod to the end of the list
 * @Head: the pointer address to the Head nod
 * @strg: strg field of nod
 * @numb: nod indx used by history
 * Return: size of list
 */
list_t *add_node_end(list_t **Head, const char *strg, int numb)
{
	list_t *newNode, *nod;

	if (!Head)
		return (NULL);
	nod = *Head;
	newNode = malloc(sizeof(list_t));
	if (!newNode)
		return (NULL);
	_memset((void *)newNode, 0, sizeof(list_t));
	newNode->numb = numb;
	if (strg)
	{
	newNode->strg = _strdup(strg);
	if (!newNode->strg)
	{
	free(newNode);
	return (NULL);
	}
	}
	if (nod)
	{
	while (nod->nxt)
	{
	nod = nod->nxt;
	}
	nod->nxt = newNode;
	}
	else
		*Head = newNode;
	return (newNode);
}

/**
 * print_list_str - A function that prints only the strg element
 * of a list_t linked list
 * @b: the pointer to the first nod
 * Return: x size of list
 */

size_t print_list_str(const list_t *b)

{
	size_t s = 0;

	while (b)
	{
	_puts(b->strg ? b->strg : "(nil)");
	_puts("\n");
	b = b->nxt;
	s++;
	}
	return (s);
}

/**
 * delete_node_at_index - A function that deletes nod at given indx
 * @Head: the address of the pointer to first nod
 * @indx: the indx of nod to delete
 * Return: 1 (successful) 0 (Unsuccessful)
 */
int delete_node_at_index(list_t **Head, unsigned int indx)
{
	list_t *nod, *prevNode;
	unsigned int s = 0;

	if (!Head || !*Head)
		return (0);
	if (!indx)
	{
	nod = *Head;
	*Head = (*Head)->nxt;
	free(nod->strg);
	free(nod);
	return (1);
	}
	nod = *Head;
	while (nod)
	{
	if (s == indx)
	{
	prevNode->nxt = nod->nxt;
	free(nod->strg);
	free(nod);
	return (1);
	}
	s++;
	prevNode = nod;
	nod = nod->nxt;
	}
	return (0);
}

/**
 * free_list - A function that frees all nodes of a list
 * @head_pointer: the address of the pointer to Head node
 * Return: void
 */

void free_list(list_t **head_pointer)

{
	list_t *nod, *nextNode, *Head;

	if (!head_pointer || !*head_pointer)
	{
	return;
	}
	Head = *head_pointer;
	nod = Head;
	while (nod)
	{
	nextNode = nod->nxt;
	free(nod->strg);
	free(nod);
	nod = nextNode;
	}
	*head_pointer = NULL;
}
