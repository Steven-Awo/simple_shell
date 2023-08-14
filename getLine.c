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
	static char *buf; /* the ';' command chain buffer */
	static size_t a, b, lengt;
	ssize_t x = 0;
	char **buf_p = &(infor->arg), *p;

	_putchar(BUF_FLUSH);
	x = input_buf(infor, &buf, &lengt);
	if (x == -1) /* EOF */
		return (-1);
	if (lengt) /* we have commands left in the chain buffer */
	{
	b = a; /* init new iterator to current buf position */
	p = buf + a; /* get pointer for return */
	check_chain(infor, buf, &b, a, lengt);
	while (b < lengt) /* iterate to semicolon or end */
	{
	if (is_chain(infor, buf, &b))
	{
	break;
	}
	b++;
	}
	a = b + 1; /* increment past nulled ';'' */
	if (a >= lengt) /* reached end of buffer? */
	{
	a = lengt = 0; /* reset position and length */
	infor->cmd_buf_type = CMD_NORM;
	}
	*buf_p = p; /* pass back pointer to current command position */
	return (_strlen(p)); /* return length of current command */
	}
	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (x); /* return length of buffer from _getline() */
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
