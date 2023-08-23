#include "shell.h"

/**
 * _strcpy - A function that copies a string
 * @destn: the destination of the address
 * @sorc: the source of the address
 * Return: destination pointer
 */

char *_strcpy(char *destn, char *sorc)

{
	int x = 0;

	if (destn == sorc || sorc == 0)
	{
	return (destn);
	}
	while (sorc[x])
	{
	destn[x] = sorc[x];
	x++;
	}
	destn[x] = 0;
	return (destn);
}

/**
 * _strdup - A function that duplicates a string
 * @str: the string to be duplicate
 * Return: the duplicated string's pointer
 */

char *_strdup(const char *str)

{
	int lenth = 0;
	char *retn;

	if (str == NULL)
	{
	return (NULL);
	}
	while (*str++)
	{
	lenth++;
	}
	retn = malloc(sizeof(char) * (lenth + 1));
	if (!retn)
	{
	return (NULL);
	}
	for (lenth++; lenth--;)
	{
	retn[lenth] = *--str;
	}
	return (retn);
}

/**
 * _puts - A function that prints out an input string
 * @str: the string that is to be printed
 * Return: Void
 */

void _puts(char *str)

{
	int x = 0;

	if (!str)
	{
	return;
	}
	while (str[x] != '\0')
	{
	_putchar(str[x]);
	x++;
	}
}

/**
 * _putchar - A function that writes the char c to stdout
 * @c: The character to be print
 * Return: 1 (successful)
 * On error, -1 is returned, and errno is set appropriately.
 */

int _putchar(char c)

{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
	write(1, buf, x);
	x = 0;
	}
	if (c != BUF_FLUSH)
	{
	buf[x++] = c;
	}
	return (1);
}
