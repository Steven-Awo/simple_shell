#include "shell.h"

/**
 * input_buf - A function that buffers the chained commands
 * @infor: the parameter structure
 * @buf: the address of the buffer
 * @leng: address of leng var
 * Return: the bytes read x (successful)
 */

ssize_t input_buf(infor_t *infor, char **buf, size_t *leng)
{
	ssize_t x = 0;
	size_t leng_p = 0;

	if (!*leng) /* if nothing left in the buffer, fill it */
	{
	/*bfree((void **)infor->cmd_buf);*/
	free(*buf);
	*buf = NULL;
	signal(SIGINT, sigintHandler);
#if USE_GETLINE
	x = getline(buf, &leng_p, stdin);
#else
	x = _getline(infor, buf, &leng_p);
#endif
	if (x > 0)
	{
	if ((*buf)[x - 1] == '\n')
	{
	(*buf)[x - 1] = '\0'; /* remove trailing newline */
	x--;
	}
	infor->linecount_of_flag = 1;
	remove_comments(*buf);
	build_history_list(infor, *buf, infor->hist_count++);
	/* if (_strchr(*buf, ';')) is this a command chain? */
	{
	*leng = x;
	infor->cmd_buf = buf;
	}
	}
	}
	return (x);
}

/**
 * get_input - A function that gets whats in a line minus
 * the newline.
 * @infor: A parameter structure
 * Return: bytes read
 */

ssize_t get_input(infor_t *infor)
{
	static char *bufr;
	static size_t x, y, lent;
	ssize_t q = 0;
	char **buff_j = &(infor->arg), *j;

	_putchar(BUF_FLUSH);
	q = input_buf(infor, &bufr, &lent);
	if (q == -1)
		return (-1);
	if (lent)
	{
	y = x;
	j = bufr + x;
	check__chain(infor, bufr, &y, x, lent);
	while (y < lent)
	{
	if (is__chain(infor, bufr, &y))
		break;
	y++;
	}
	x = y + 1;
	if (x >= lent)
	{
	x = lent = 0;
	infor->cmd_buf_type = CMD_NORM;
	}
	*buff_j = j;
	return (_strlen(j));
	}
	*buff_j = bufr;
	return (q);
}

/**
 * read_buf - A function that reads a buffer
 * @infor: A parameter structure
 * @buf: The buffer
 * @a: the size
 * Return: x (successful)
 */

ssize_t read_buf(infor_t *infor, char *buf, size_t *a)

{
	ssize_t x = 0;

	if (*a)
	{
	return (0);
	}
	x = read(infor->read_fd, buf, READ_BUF_SIZE);
	if (x >= 0)
	{
	*a = x;
	}
	return (x);
}

/**
 * _getline - A function that gets the next line of
 * input from STDIN
 * @infor: A parameter structure
 * @potr: The pointer address to buffer, NULL or preallocated
 * @length: The size of preallocated potr buffer if not NULL
 * Return: y (successful)
 */

int _getline(infor_t *infor, char **potr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t a, lengt;
	size_t z;
	ssize_t x = 0, y = 0;
	char *o = NULL, *new_pt = NULL, *l;

	o = *potr;
	if (o && length)
		y = *length;
	if (a == lengt)
		a = lengt = 0;
	x = read_buf(infor, buf, &lengt);
	if (x == -1 || (x == 0 && lengt == 0))
		return (-1);
	l = _strchr(buf + a, '\n');
	z = l ? 1 + (unsigned int)(l - buf) : lengt;
	new_pt = _realloc(o, y, y ? y + z : z + 1);
	if (!new_pt) /* MALLOC FAILURE! */
		return (o ? free(o), -1 : -1);
	if (y)
		_strncat(new_pt, buf + a, z - a);
	else
		_strncpy(new_pt, buf + a, z - a + 1);
	y += z - a;
	a = z;
	o = new_pt;
	if (length)
		*length = y;
	*potr = o;
	return (y);
}

/**
 * sigintHandler - A function that blocks ctrl-C command
 * @sigl_num: the number for the signal
 * Return: void nothing
 */

void sigintHandler(__attribute__((unused))int sigl_num)

{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
