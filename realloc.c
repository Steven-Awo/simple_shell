#include "shell.h"

/**
 * _memset - A function that fills memory with
 * a particular constant byte
 * @k: A pointer to the memory's area
 * @l: the byte(k) to fill *k with
 * @m: the amount of bytes to be filled
 * Return: (k) a pointer to the memory area k
 */

char *_memset(char *k, char l, unsigned int m)

{
	unsigned int x;

	for (x = 0; x < m; x++)
	{
	k[x] = l;
	}
	return (k);
}

/**
 * ffree - A function that frees up a string of
 * strings
 * @spp: string of strings
 * Return: void
 */

void ffree(char **spp)

{
	char **a = spp;

	if (!spp)
	{
	return;
	}
	while (*spp)
	{
	free(*spp++);
	}
	free(a);
}

/**
 * _realloc - A function that reallocates a memory block
 * @ptr: A pointer to the prevs malloc'ated block
 * @old_size: the previous block size in bytes
 * @new_size: the new block byte size
 * Return: pointer to da ol'block nameen.
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *ps;

	if (!ptr)
	{
	return (malloc(new_size));
	}
	if (!new_size)
	{
	return (free(ptr), NULL);
	}
	if (new_size == old_size)
	{
	return (ptr);
	}
	ps = malloc(new_size);
	if (!ps)
	{
	return (NULL);
	}
	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
	{
	ps[old_size] = ((char *)ptr)[old_size];
	}
	free(ptr);
	return (ps);
}
