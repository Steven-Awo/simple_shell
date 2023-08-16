#include "shell.h"

/**
 * _strrlen - This function returns the length of a string
 * @b: This is the string whose length to check
 *
 * Return: integer length of string
 */
int _strrlen(char *b)
{
	int e = 0;

	if (!b)
		return (0);

	while (*b++)
		e++;
	return (e);
}

/**
 * _strrcmp - This function performs lexicogarphic comparison of two strangs.
 * @b1: This is the first strang
 * @b2: This is the second strang
 *
 * Return: negative if b1 < b2, positive if b1 > b2, zero if b1 == b2
 */
int _strrcmp(char *b1, char *b2)
{
	while (*b1 && *b2)
	{
		if (*b1 != *b2)
			return (*b1 - *b2);
		b1++;
		b2++;
	}
	if (*b1 == *b2)
		return (0);
	else
		return (*b1 < *b2 ? -1 : 1);
}

/**
 * starrts_with - This function checks if needle starts with haystacckk
 * @haystacckk: This is string to search
 * @needle: This is the substring to find
 *
 * Return: address of next char of haystacckk or NULL
 */
char *starrts_with(const char *haystacckk, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystacckk++)
			return (NULL);
	return ((char *)haystacckk);
}

/**
 * _strrcatt - This function concatenates two strings
 * @desstt: This is the destination buffer
 * @srrcc: This is the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strrcatt(char *desstt, char *srrcc)
{
	char *ret = desstt;

	while (*desstt)
		desstt++;
	while (*srrcc)
		*desstt++ = *srrcc++;
	*desstt = *srrcc;
	return (ret);
}
