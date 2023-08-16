#include "shell.h"

/**
 * _strrcpy - This functioncopies a string
 * @desstt: This is the destination
 * @srrcc: This is the source
 *
 * Return: pointer to dessttination
 */
char *_strrcpy(char *desstt, char *srrcc)
{
	int e = 0;

	if (desstt == srrcc || srrcc == 0)
		return (desstt);
	while (srrcc[e])
	{
	desstt[e] = srrcc[e];
	e++;
	}
	desstt[e] = 0;
	return (desstt);
}

/**
 * _strrdup - This function duplicates a string
 * @strr: This is the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strrdup(const char *strr)
{
	int length = 0;
	char *ret;

	if (strr == NULL)
		return (NULL);
	while (*strr++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--strr;
	return (ret);
}

/**
 * _putts - This function prints an input string
 * @strr: This is the string to be printed
 *
 * Return: Nothing
 */
void _putts(char *strr)
{
	int e = 0;

	if (!strr)
		return;
	while (strr[e] != '\0')
	{
		_putchar(strr[e]);
		e++;
	}
}

/**
 * _putchar - This funtion writes the character k to stdout
 * @k: This is the character to print
 *
 * Return: if successful 1.
 * if error returned -1 , and errno is set appropriately.
 */
int _putchar(char k)
{
	static int e;
	static char buf[WRITE_BUF_SIZE];

	if (k == BUF_FLUSH || e >= WRITE_BUF_SIZE)
	{
	write(1, buf, e);
	e = 0;
	}
	if (k != BUF_FLUSH)
		buf[e++] = k;
	return (1);
}
