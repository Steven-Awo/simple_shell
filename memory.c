#include "shell.h"

/**
 * bbfreee - This function works to free a pointer and NULLs the address
 * @ptrrr: This is the address of the pointer to free
 *
 * Return: 1 if freed, if not freed 0.
 */
int bbfreee(void **ptrrr)
{
	if (ptrrr && *ptrrr)
	{
		free(*ptrrr);
		*ptrrr = NULL;
		return (1);
	}
	return (0);
}
