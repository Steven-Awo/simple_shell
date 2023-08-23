#include "shell.h"

/**
 * b_free - A function that frees or releases a pointer and
 * NULLs the address
 * @pntr: the address of the pointer to the free
 * Return: 1 (freed) or 0 (otherwise)
 */

int b_free(void **pntr)

{
	if (pntr && *pntr)
	{
	free(*pntr);
	*pntr = NULL;
	return (1);
	}
	return (0);
}
