#include "shell.h"

/**
 * _memsett - This function fills memory with a constant byte
 * @a: TThis is the pointer to the memory area
 * @b: This is the byte to fill *s with
 * @n: This is the amount of bytes to be filled
 * Return: a pointer to the memory area a
 */
char *_memsett(char *a, char b, unsigned int n)
{
	unsigned int v;

	for (v = 0; v < n; v++)
		a[v] = b;
	return (a);
}

/**
 * frree - This function frees a string of strings
 * @ppx: This is string of strings
 */
void frree(char **ppx)
{
	char **a = ppx;

	if (!ppx)
		return;
	while (*ppx)
		free(*ppx++);
	free(a);
}

/**
 * _rreallocc - This function reallocates a block of memory
 * @ptrr: This is the pointer to previous mallocated block
 * @old_sizee: This is the byte size of previous block
 * @neww_size: This is the byte size of new block
 *
 * Return: pointer to da old block
 */
void *_rreallocc(void *ptrr, unsigned int old_sizee, unsigned int neww_size)
{
	char *p;

	if (!ptrr)
		return (malloc(neww_size));
	if (!neww_size)
		return (free(ptrr), NULL);
	if (neww_size == old_sizee)
		return (ptrr);

	p = malloc(neww_size);
	if (!p)
		return (NULL);

	old_sizee = old_sizee < neww_size ? old_sizee : neww_size;
	while (old_sizee--)
		p[old_sizee] = ((char *)ptrr)[old_sizee];
	free(ptrr);
	return (p);
}
