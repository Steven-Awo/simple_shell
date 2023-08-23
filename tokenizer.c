#include "shell.h"

/**
 * _strlen - A function that returns a strings length
 * @a: the string whose length to check
 * Return: integer length of string
 */

int _strlen(char *a)
{
	int x = 0;

	if (!a)
	{
	return (0);
	}
	while (*a++)
	{
	x++;
	}
	return (x);
}

/**
 * _strcmp - A function that performs a lexicogarphic comparison
 * of two diff strangs.
 * @strg1: the 1st strang
 * @strg2: the 2nd strang
 * Return: strg1 < strg2(negative) or strg1 > strg2(posotive)
 * or strg1 == strg2(zero)
 */

int _strcmp(char *strg1, char *strg2)

{
	while (*strg1 && *strg2)
	{
	if (*strg1 != *strg2)
	{
	return (*strg1 - *strg2);
	}
	strg1++;
	strg2++;
	}
	if (*strg1 == *strg2)
	{
	return (0);
	}
	else
	{
	return (*strg1 < *strg2 ? -1 : 1);
	}
}

/**
 * starts_with - A function that checks if the nedle
 * starts with hay_stack
 * @hay_stack: the string for search
 * @nedle: the substring to find
 * Return: hay_stack (the next char address of hay_stack) or NULL
 */

char *starts_with(const char *hay_stack, const char *nedle)

{
	while (*nedle)
	{
	if (*nedle++ != *hay_stack++)
	{
	return (NULL);
	}
	}
	return ((char *)hay_stack);
}

/**
 * _strcat - A function that concatenates two diff strings
 * @desti: the destination'a buffer
 * @sorc: the buffer of the source
 * Return: pointer to destination buffer
 */

char *_strcat(char *desti, char *sorc)

{
	char *retn = desti;

	while (*desti)
	{
	desti++;
	}
	while (*sorc)
	{
	*desti++ = *sorc++;
	}
	*desti = *sorc;
	return (retn);
}
