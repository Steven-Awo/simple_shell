#include "shell.h"

/**
 * **strtow1 - A function that splits or div a string into words.
 * When repeat delimiters are see they are ignored
 * @strng: the inputed string
 * @s_d: the string that is a delimeter
 * Return: (an array pointer of strings) or NULL (unsuccessful)
 */

char **strtow1(char *strng, char *s_d)
{
	int x, y, a, b, num_words = 0;
	char **q;

	if (strng == NULL || strng[0] == 0)
		return (NULL);
	if (!s_d)
		s_d = " ";
	for (x = 0; strng[x] != '\0'; x++)
		if (!is_delim(strng[x], s_d) && (is_delim(strng[x + 1], s_d)
					|| !strng[x + 1]))
			num_words++;
	if (num_words == 0)
		return (NULL);
	q = malloc((1 + num_words) * sizeof(char *));
	if (!q)
		return (NULL);
	for (x = 0, y = 0; y < num_words; y++)
	{
	while (is_delim(strng[x], s_d))
		x++;
	a = 0;
	while (!is_delim(strng[x + a], s_d) && strng[x + a])
		a++;
	q[y] = malloc((a + 1) * sizeof(char));
	if (!q[y])
	{
	for (a = 0; a < y; a++)
		free(q[a]);
	free(q);
	return (NULL);
	}
	for (b = 0; b < a; b++)
		q[y][b] = strng[x++];
	q[y][b] = 0;
	}
	q[y] = NULL;
	return (q);
}

/**
 * **strtow2 - A function that creates words by spliting a string
 * @strng: the inputed string
 * @s_d: the string of a delimeter
 * Return: q (an array pointer of strings) or NULL (unsuccessful)
 */
char **strtow2(char *strng, char s_d)
{
	int x, y, a, b, num_words = 0;
	char **q;

	if (strng == NULL || strng[0] == 0)
		return (NULL);
	for (x = 0; strng[x] != '\0'; x++)
		if ((strng[x] != s_d && strng[x + 1] == s_d) ||
				    (strng[x] != s_d && !strng[x + 1]) || strng[x + 1] == s_d)
			num_words++;
	if (num_words == 0)
		return (NULL);
	q = malloc((1 + num_words) * sizeof(char *));
	if (!q)
		return (NULL);
	for (x = 0, y = 0; y < num_words; y++)
	{
	while (strng[x] == s_d && strng[x] != s_d)
		x++;
	a = 0;
	while (strng[x + a] != s_d && strng[x + a] && strng[x + a] != s_d)
		a++;
	q[y] = malloc((a + 1) * sizeof(char));
	if (!q[y])
	{
	for (a = 0; a < y; a++)
		free(q[a]);
	free(q);
	return (NULL);
	}
	for (b = 0; b < a; b++)
		q[y][b] = strng[x++];
	q[y][b] = 0;
	}
	q[y] = NULL;
	return (q);
}
