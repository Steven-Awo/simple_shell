#include "shell.h"

/**
 * is_cmd - A function that determines if a file
 * is really an executable command or not
 * @infor: the inforr structure
 * @path_way: the path_way to the file
 * Return: 1 (true) or 0 (otherwise)
 */

int is_cmd(infor_t *infor, char *path_way)

{
	struct stat strt;

	(void)infor;
	if (!path_way || stat(path_way, &strt))
	{
	return (0);
	}
	if (strt.st_mode & S_IFREG)
	{
	return (1);
	}
	return (0);
}

/**
 * dup_chars - a function that duplicates characters
 * @path_str: the PATH way string
 * @starts: the startsing index
 * @stops: the stopsping index
 * Return: pointer to new buffer
 */

char *dup_chars(char *path_str, int starts, int stops)

{
	static char buf[1024];
	int x = 0;
	int y = 0;

	for (y = 0, x = starts; x < stops; x++)
	{
	if (path_str[x] != ':')
	{
	buf[y++] = path_str[x];
	}
	}
	buf[y] = 0;
	return (buf);
}

/**
 * find_path - A function that finds the cmd
 * in the PATH string
 * @infor: the infor structure
 * @path_str: the PATH string
 * @cmd: the cmd to be found
 * Return: full path_way of cmd if found or NULL
 */
char *find_path(infor_t *infor, char *path_str, char *cmd)
{
	int x = 0, currt_pos = 0;
	char *path_way;

	if (!path_str)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
	if (is_cmd(infor, cmd))
		return (cmd);
	}
	while (1)
	{
	if (!path_str[x] || path_str[x] == ':')
	{
	path_way = dup_chars(path_str, currt_pos, x);
	if (!*path_way)
		_strcat(path_way, cmd);
	else
	{
	_strcat(path_way, "/");
	_strcat(path_way, cmd);
	}
	if (is_cmd(infor, path_way))
		return (path_way);
	if (!path_str[x])
		break;
	currt_pos = x;
	}
	x++;
	}
	return (NULL);
}
