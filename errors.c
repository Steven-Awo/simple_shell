#include "shell.h"

/**
 * _eputs - A program that prints an input string
 * @strg: the string that is to be printed
 * Return: void
 */

void _eputs(char *strg)

{
	int d = 0;

	if (!strg)
	{
	return;
	}
	while (strg[d] != '\0')
	{
	_eputchar(strg[d]);
	d++;
	}
}

/**
 * _eputchar - A function that writes the character x to stderr
 * @x: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _eputchar(char x)

{
	static int d;
	static char buf[WRITE_BUF_SIZE];

	if (x == BUF_FLUSH || d >= WRITE_BUF_SIZE)
	{
	write(2, buf, d);
	d = 0;
	}
	if (x != BUF_FLUSH)
	{
	buf[d++] = x;
	}
	return (1);
}

/**
 * _putfd - A function that writes the character x to the given fid
 * @x: its the character to be printed
 * @fid: The filedescriptor to be written to
 * Return: 1 (successful)
 * On error, -1 is returned, and errno is set appropriately.
 */

int _putfd(char x, int fid)

{
	static int d;
	static char buf[WRITE_BUF_SIZE];

	if (x == BUF_FLUSH || d >= WRITE_BUF_SIZE)
	{
	write(fid, buf, d);
	d = 0;
	}
	if (x != BUF_FLUSH)
	{
	buf[d++] = x;
	}
	return (1);
}

/**
 * _putsfd - A function that prints an input thats a string
 * @strg: the string for printing
 * @fid: the filedescriptor for writing to
 * Return: d (auccessfull)the number of chars
 */

int _putsfd(char *strg, int fid)

{
	int d = 0;

	if (!strg)
	{
	return (0);
	}
	while (*strg)
	{
	d += _putfd(*strg++, fid);
	}
	return (d);
}
