#include "shell.h"

/**
 * interactive - A program that returns true if the
 * shell is in interactive mode
 * @infor: the address of the struct
 * Return: 1 (Successful) or 0 (unsuccessful)
 */

int interactive(infor_t *infor)

{
	return (isatty(STDIN_FILENO) && infor->read_fd <= 2);
}

/**
 * is_delim - A program that checks if a character is a delimeter
 * @x: the char to check
 * @delimr: the delimeter string
 * Return: 1 (true) or 0 (false)
 */

int is_delim(char x, char *delimr)

{
	while (*delimr)
	{
	if (*delimr++ == x)
	{
	return (1);
	}
	}
	return (0);
}

/**
 * _isalpha - A proram that checks for alphabetic character
 * @x: The character to be input
 * Return: 1 (alphabetical) or 0 (non-alphabetical)
 */

int _isalpha(int x)

{
	if ((x <= 'z' && x >= 'a') || (x <= 'Z' && x >= 'A'))
	{
	return (1);
	}
	else
	{
	return (0);
	}
}

/**
 * _atoi - A progamed fuction that converts a str to an int
 * @x: the string to be converted to an int
 * Return: out_put (coverted number) or 0 (not a string)
 */

int _atoi(char *x)
{
	int a, sig = 1, flg = 0, out_put;
	unsigned int results = 0;

	for (a = 0; x[a] != '\0' && flg != 2; a++)
	{
	if (x[a] == '-')
	{
	sig *= -1;
	}
	if (x[a] >= '0' && x[a] <= '9')
	{
	flg = 1;
	results *= 10;
	results += (x[a] - '0');
	}
	else if (flg == 1)
	{
	flg = 2;
	}
	}
	if (sig == -1)
	{
	out_put = -results;
	}
	else
	{
	out_put = results;
	}
	return (out_put);
}
