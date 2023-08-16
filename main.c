#include "shell.h"

/**
 * main - This is the entry point
 * @aacc: This is the arg count
 * @aavv: This is the arg vector
 *
 * Return: 0 if successful, 1 if error
 */
int main(int aacc, char **aavv)
{
	infor_t infor[] = { INFO_INIT };
	int mn = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (mn)
			: "r" (mn));

	if (aacc == 2)
	{
	mn = open(aavv[1], O_RDONLY);
	if (mn == -1)
	{
	if (errno == EACCES)
	exit(126);
	if (errno == ENOENT)
	{
	_eputs(aavv[0]);
	_eputs(": 0: Can't open ");
	_eputs(aavv[1]);
	_eputchar('\n');
	_eputchar(BUF_FLUSH);
	exit(127);
	}
	return (EXIT_FAILURE);
	}
	infor->readmn = mn;
	}
	populate_env_list(infor);
	read_history(infor);
	hsh(infor, aavv);
	return (EXIT_SUCCESS);
}
