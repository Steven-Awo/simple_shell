#include "shell.h"

/**
 * _myexit - A function that exits the shell
 * @infor: the structure that contains potential arguments.
 * Used to maintain constant function prototype.
 * Return: exits with a given exit status
 * (0) if infor.argv[0] != "exit"
 */

int _myexit(infor_t *infor)
{
	int exit_check;

	if (infor->argv[1]) /* If there is an exit arguement */
	{
	exit_check = _erratoi(infor->argv[1]);
	if (exit_check == -1)
	{
	infor->status = 2;
	print_error(infor, "Illegal number: ");
	_eputs(infor->argv[1]);
	_eputchar('\n');
	return (1);
	}
	infor->err_numb = _erratoi(infor->argv[1]);
	return (-2);
	}
	infor->err_numb = -1;
	return (-2);
}

/**
 * _mycd - A progranedcfuction that changes the process
 * current directory
 * @infor: the structure that contains potential arguments.
 * Used to maintain constant function prototype.
 * Return: 0 (Always)
 */

int _mycd(infor_t *infor)

{
	char *x, *diry, buffer[1024];
	int chdiry_ret;

	x = getcwd(buffer, 1024);
	if (!infor->argv[1])
	{
	diry = _getenv(infor, "HOME=");
	if (!diry)
		chdiry_ret =/* TODO: what should this be? */
			chdir((diry = _getenv(infor, "PWD=")) ? diry : "/");
	else
		chdiry_ret = chdir(diry);
	}
	if (!x)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	else if (_strcmp(infor->argv[1], "-") == 0)
	{
	if (!_getenv(infor, "OLDPWD="))
	{
	_puts(x);
	_putchar('\n');
	return (1);
	}
	_puts(_getenv(infor, "OLDPWD=")), _putchar('\n');
	chdiry_ret = /* TODO: what should this be for? */
		chdir((diry = _getenv(infor, "OLDPWD=")) ? diry : "/");
	}
	else
		chdiry_ret = chdir(infor->argv[1]);
	if (chdiry_ret == -1)
	{
	print_error(infor, "can't cd to ");
	_eputs(infor->argv[1]), _eputchar('\n');
	}
	else
	{
	_setenv(infor, "OLDPWD", _getenv(infor, "PWD="));
	_setenv(infor, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - A program that changes the process current directory
 * @infor: the structure that contains potential arguments.
 * Used to maintain constant function prototype.
 * Return: 0 (always)
 */

int _myhelp(infor_t *infor)

{
	char **arg_arry;

	arg_arry = infor->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
	{
	_puts(*arg_arry); /* temp att_unused workaround */
	}
	return (0);
}
