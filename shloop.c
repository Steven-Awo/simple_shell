#include "shell.h"

/**
 * hsh -This is the main shell loop
 * @infor: This is the parameter & return infor struct
 * @avv: This is the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(infor_t *infor, char **avv)
{
	ssize_t w = 0;
	int builtin_rret = 0;

	while (w != -1 && builtin_rret != -2)
	{
		clear_info(infor);
		if (interactive(infor))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		w = get_input(infor);
		if (w != -1)
		{
		set_info(infor, avv);
		builtin_rret = find_builtin(infor);
		if (builtin_rret == -1)
		find_cmdd(infor);
		}
		else if (interactive(infor))
		putchar('\n');
		free_infor(infor, 0);
	}
	write_history(infor);
	free_infor(infor, 1);
	if (!interactive(infor) && infor->status)
		exit(infor->status);
	if (builtin_rret == -2)
	{
		if (infor->err_numb == -1)
			exit(infor->status);
		exit(infor->err_numb);
	}
	return (builtin_rret);
}

/**
 * find_builtinn - This function finds a builtin command
 * @infor: This is the parameter & return infor struct
 *
 * Return: -1 if builtin not found,
 * 0 if builtin is successful,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit()
 */
int find_builtinn(infor_t *infor)
{
	int w, built_in_rret = -1;
	builtin_table builtintbl[] = {
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

	for (w = 0; builtintbl[w].type; w++)
		if (_strcmp(infor->argv[0], builtintbl[w].type) == 0)
		{
		infor->line_counts++;
		built_in_rret = builtintbl[w].func(infor);
		break;
		}
	return (built_in_rret);

}
/**
 * find_cmdd -This function finds a command in PATH
 * @infor: This is the parameter & return infor struct
 *
 * Return: void
 */
void find_cmdd(infor_t *infor)
{
	char *path = NULL;
	int w, r;

	infor->path = infor->argv[0];
	if (infor->linecount_of_flag == 1)
	{   infor->line_counts++;
	infor->linecount_of_flag = 0;
	}
	for (w = 0, r = 0; infor->arg[w]; w++)
		if (!is_delim(infor->arg[w], " \t\n"))
			r++;
	if (!r)
		return;

	path = find_path(infor, _getenv(infor, "PATH="), infor->argv[0]);
	if (path)
	{
		infor->path = path;
		forrk_cmdd(infor);
	}
	else
	{
		if ((interactive(infor) || _getenv(infor, "PATH=")
					|| infor->argv[0][0] == '/') && is_cmd(infor, infor->argv[0]))
			forrk_cmdd(infor);
		else if (*(infor->arg) != '\n')
		{
			infor->status = 127;
			print_error(infor, "not found\n");
		}
	}
}

/**
 * forrk_cmdd - This function forks a an exec thread to run cmd
 * @infor: This is the parameter & return infor struct
 *
 * Return: void
 */
void forrk_cmdd(infor_t *infor)
{
	pid_t child_pid;

	child_pid = forrk();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
}
	if (child_pid == 0)
	{
		if (execve(infor->path, infor->argv, get_environ(infor)) == -1)
		{
			free_infor(infor, 1);
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
