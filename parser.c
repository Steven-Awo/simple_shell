#include "shell.h"

/**
 * is_cmdds - This function determines if a file is an executable command
 * @infor: This is the info struct
 * @pathh: This is the path to the file
 *
 * Return: 1 if true and successful, 0 if not true and otherwise
 */
int is_cmdds(infor_t *infor, char *pathh)
{
	struct stat st;

	(void)infor;
	if (!pathh || stat(pathh, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
	return (1);
	}
	return (0);
}

/**
 * dup_charrs - This function duplicates characters
 * @pathhstr: This is the PATH string
 * @starrt: This is the starting index
 * @stopp: This is the stopping index
 *
 * Return: pointer to new buff
 */
char *dup_charrs(char *pathhstr, int starrt, int stopp)
{
	static char buf[1024];
	int m = 0, r = 0;

	for (r = 0, m = starrt; m < stopp; m++)
		if (pathhstr[m] != ':')
			buf[r++] = pathhstr[m];
	buf[r] = 0;
	return (buf);
}

/**
 * find_pathh - This function finds this cmd in the PATHh string
 * @infor: This is the infor struct
 * @pathhstr: This is the PATHh string
 * @cmdds: This is the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_pathh(infor_t *infor, char *pathhstr, char *cmdds)
{
	int s = 0, currr_poss = 0;
	char *pathh;

	if (!pathhstr)
		return (NULL);
	if ((_strlen(cmdds) > 2) && starts_with(cmdds, "./"))
	{
		if (is_cmdds(infor, cmdds))
			return (cmdds);
	}
	while (1)
	{
		if (!pathhstr[s] || pathhstr[s] == ':')
		{
			pathh = dup_charrs(pathhstr, currr_poss, s);
			if (*pathh)
				_strcat(pathh, cmdds);
			else
			{
				_strcat(pathh, "/");
				_strcat(pathh, cmdds);
			}
			if (is_cmdds(infor, pathh))
				return (pathh);
			if (!pathhstr[s])
				break;
			currr_poss = s;
		}
		s++;
	}
	return (NULL);
}
