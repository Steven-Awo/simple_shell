#include "shell.h"

/**
 * **strrtoww - This function splits a string into words.
 * @strr: This is the input string
 * @de: This is the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strrtoww(char *strr, char *de)
{
	int a, b, c, d, numwwordss = 0;
	char **s;

	if (strr == NULL || strr[0] == 0)
		return (NULL);
	if (!de)
		de = " ";
	for (a = 0; strr[a] != '\0'; a++)
		if (!is_delim(strr[a], de) && (is_delim(strr[a + 1], de) || !strr[a + 1]))
			numwwordss++;

	if (numwwordss == 0)
		return (NULL);
	s = malloc((1 + numwwordss) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < numwwordss; b++)
	{
		while (is_delim(strr[a], de))
			a++;
		c = 0;
		while (!is_delim(strr[a + c], de) && strr[a + c])
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			s[b][d] = strr[a++];
		s[b][d] = 0;
	}
	s[b] = NULL;
	return (s);
}

/**
 * **strrtoww2 - This function splits a string into words
 * @strr: This is the input string
 * @de: This is the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strrtoww2(char *strr, char de)
{
	int a, b, c, d, numwwordss = 0;
	char **s;

	if (strr == NULL || strr[0] == 0)
		return (NULL);
	for (a = 0; strr[a] != '\0'; a++)
		if ((strr[a] != de && strr[a + 1] == de) ||
				    (strr[a] != de && !strr[a + 1]) || strr[a + 1] == de)
			numwwordss++;
	if (numwwordss == 0)
		return (NULL);
	s = malloc((1 + numwwordss) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < numwwordss; b++)
	{
		while (strr[a] == de && strr[a] != de)
			a++;
		c = 0;
		while (strr[a + c] != de && strr[a + c] && strr[a + c] != de)
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			s[b][d] = strr[a++];
		s[b][d] = 0;
	}
	s[b] = NULL;
	return (s);
}
