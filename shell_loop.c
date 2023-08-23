#include "shell.h"

/**
 * hsh -The function shows the main shell loop
 * @infor: This is the parameter & return infor struct
 * @avg: This is the argument vector from main()
 * Return: 0 on success, 1 on error, or error code
 */

int hsh(infor_t *infor, char **avg)
{
	ssize_t a = 0;
	int builtin_retn = 0;

	while (a != -1 && builtin_retn != -2)
	{
	clear_info(infor);
	if (interactive(infor))
		_puts("$ ");
	_eputchar(BUF_FLUSH);
	a = get_input(infor);
	if (a != -1)
	{
	set_info(infor, avg);
	builtin_retn = find_builtin(infor);
	if (builtin_retn == -1)
		find_cmd(infor);
	}
	else if (interactive(infor))
		_putchar('\n');
	free_info(infor, 0);
	}
	write_history(infor);
	free_info(infor, 1);
	if (!interactive(infor) && infor->status)
		exit(infor->status);
	if (builtin_retn == -2)
	{
	if (infor->err_numb == -1)
		exit(infor->status);
	exit(infor->err_numb);
	}
	return (builtin_retn);
}

/**
 * find_builtin - This function finds a builtin command
 * @infor: This is the parameter & return infor struct
 * Return: -1 if builtin not found,
 * 0 if the builtin is (successful),
 * 1 if the builtin is found but not yet successful,
 * 2 if the builtin's signals exit()
 */

int find_builtin(infor_t *infor)
{
	int x, built_in_retn = -1;
	builtin_table builtin_tbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};
	for (x = 0; builtin_tbl[x].type; x++)
		if (_strcmp(infor->argv[0], builtin_tbl[x].type) == 0)
		{
		infor->line_counts++;
		built_in_retn = builtin_tbl[x].func(infor);
		break;
		}
	return (built_in_retn);
}

/**
 * find_cmd -This function finds a command in PATH
 * @infor: This is the parameter & return infor struct
 * Return: void
 */

void find_cmd(infor_t *infor)
{
	char *path = NULL;
	int x, y;

	infor->path = infor->argv[0];
	if (infor->linecount_of_flag == 1)
	{
	infor->line_counts++;
	infor->linecount_of_flag = 0;
	}
	for (x = 0, y = 0; infor->arg[x]; x++)
		if (!is_delim(infor->arg[x], " \t\n"))
			y++;
	if (!y)
		return;
	path = find_path(infor, _getenv(infor, "PATH="), infor->argv[0]);
	if (path)
	{
	infor->path = path;
	fork_cmd(infor);
	}
	else
	{
	if ((interactive(infor) || _getenv(infor, "PATH=")
				|| infor->argv[0][0] == '/') && is_cmd(infor,
					infor->argv[0]))
		fork_cmd(infor);
	else if (*(infor->arg) != '\n')
	{
	infor->status = 127;
	print_error(infor, "not found\n");
	}
	}
}

/**
 * fork_cmd - This function forks a an exec thread to run cmd
 * @infor: This is the parameter & return infor structure
 * Return: void
 */

void fork_cmd(infor_t *infor)
{
	pid_t child__pid;

	child__pid = fork();
	if (child__pid == -1)
	{
	/* === TODO: PUT ERROR FUNCTION ==*/
	perror("Error:");
	return;
	}
	if (child__pid == 0)
	{
	if (execve(infor->path, infor->argv, get_environ(infor)) == -1)
	{
	free_info(infor, 1);
	if (errno == EACCES)
		exit(126);
	exit(1);
	}
	/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
	wait(&(infor->status));
	if (WIFEXITED(infor->status))
	{
	infor->status = WEXITSTATUS(infor->status);
	if (infor->status == 126)
		print_error(infor, "Permission denied\n");
	}
	}
}
