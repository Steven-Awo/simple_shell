#include "shell.h"

/**
 * main - The entry point
 * @acg: the arg count
 * @avg: the arg vector
 * Return: 0 (successful) or 1 (error)
 */
int main(int acg, char **avg)
{
	infor_t inform[] = { INFO_INIT };
	int fid = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fid)
			: "r" (fid));
	if (acg == 2)
	{
	fid = open(avg[1], O_RDONLY);
	if (fid == -1)
	{
	if (errno == EACCES)
		exit(126);
	if (errno == ENOENT)
	{
	_eputs(avg[0]);
	_eputs(": 0: Can't open ");
	_eputs(avg[1]);
	_eputchar('\n');
	_eputchar(BUF_FLUSH);
	exit(127);
	}
	return (EXIT_FAILURE);
	}
	inform->read_fd = fid;
	}
	populate_env_list(inform);
	read_history(inform);
	hsh(inform, avg);
	return (EXIT_SUCCESS);
}
