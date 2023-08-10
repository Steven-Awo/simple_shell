#include "shell.h"

/**
 **_strncpy - A function that copies a string for srce to destn
 *@destn: the destination to where the string to be copied to
 *@srce: the source to where the string to gotten copied from
 *@h: the number of characters to be copied
 *Return: the concatenated string
 */

char *_strncpy(char *destn, char *srce, int h)

{
	int x, y;
	char *b = destn;

	x = 0;
	while (srce[x] != '\0' && x < h - 1)
	{
	destn[x] = srce[x];
	x++;
	}
	if (x < h)
	{
	y = x;
	while (y < h)
	{
	destn[y] = '\0';
	y++;
	}
	}
	return (b);
}

/**
 **_strncat - A function that concatenates two strings
 *@destn: the destination of the first string
 *@srce: the source of the second string
 *@h: the maximum amount of bytes to be used
 *Return: x concatenated string
 */

char *_strncat(char *destn, char *srce, int h)

{
	int x, y;
	char *b = destn;

	x = 0;
	y = 0;
	while (destn[x] != '\0')
	{
	x++;
	}
	while (srce[y] != '\0' && y < h)
	{
	destn[x] = srce[y];
	x++;
	y++;
	}
	if (y < h)
	{
	destn[x] = '\0';
	}
	return (b);
}

/**
 **_strchr - A function that locates a character in a str
 *@d: the str to be parsed
 *@a: the chr to look for
 *Return: (x) pointer to the area of memory x
 */

char *_strchr(char *d, char a)

{
	do {
	if (*d == a)
	{
	return (d);
	}
	} while (*d++ != '\0');
	return (NULL);
}
