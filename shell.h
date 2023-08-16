#ifndef SHELL_H
#define SHELL_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>

/* To command chaining */

#define CMD_NORM        0
#define CMD_OR          1
#define CMD_AND         2
#define CMD_CHAIN       3

/*
 * To read or write buffers.
 */

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/*
 * To convert_number()
 */

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/*
 * 1 to check if its using system getline()
 */

#define USE_GETLINE 0
#define USE_STRTOK 0
#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct liststr - A fuction that singly a linked list
 * @numb: its the number field
 * @strg: its a string
 * @nxt: it points to the next node
 */

typedef struct liststr

{
	int numb;
	char *strg;
	struct liststr *nxt;
} list_t;

/**
 * struct passinfo - A function that contains pseudo-arguements that
 * pass into a function, which allows uniform prototype for
 * function pointer struct
 * @arg: its a string that was generated from getline
 * containing arguements
 * @argv: its an array of strings that was generated from arg
 * @path: its a string path used for the current command
 * @argc: the count of argument.
 * @line_counts: its the number of error count
 * @err_numb: its the error code used for exit()s
 * @linecount_of_flag: for if on count this line of input
 * @flname: its the filename of the program
 * @envir: its the linked list local copy of environment
 * @environ: its the copy of the modified custom of environ from LL env
 * @history: its the node for the history.
 * @alias: its the node for the alias.
 * @envir_changed: on if environ was changed
 * @status: its the status returned by the last exec'd command
 * @cmd_buf: its the pointer's address to cmd_buf, but on if chaining
 * @cmd_buf_type: CMD_type &&, ||, ;
 * @read_fd: its the fd from which a  line input is read
 * @hist_count: its the number of history line counted
 */

typedef struct passinfo
{
	char *arg;
	char **argv;
	int argc;
	char *path;
	unsigned int line_counts;
	int err_numb;
	int linecount_of_flag;
	char *flname;
	list_t *envir;
	list_t *history;
	list_t *alias;
	char **environ;
	int envir_changed;
	int status;
	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int read_fd;
	int hist_count;
} infor_t;

#define INFO_INIT \
{NULL, NULL, 0, NULL, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - A function that contains a builtin
 * string and related function
 * @type: its the builtin command flag
 * @func: its the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(infor_t *);
} builtin_table;

/* =========================== First Partner file ========================= */

/*
 * for _atoi.c file
 */

int interactive(infor_t *);

int is_delim(char, char *);

int _isalpha(int);

int _atoi(char *);

/*
 * for _builtin.c file
 */

int _myexit(infor_t *);

int _mycd(infor_t *);

int _myhelp(infor_t *);

/*
 * for _builtin1.c file
 */

int _myhistory(infor_t *);

int _myalias(infor_t *);

/*
 * for file _environ.c
 */

char *_getenv(infor_t *, const char *);

int _myenv(infor_t *);

int _mysetenv(infor_t *);

int _myunsetenv(infor_t *);

int populate_env_list(infor_t *);


/*
 * for file _errors.c
 */

void _eputs(char *);

int _eputchar(char);

int _putfd(char x, int fid);

int _putsfd(char *strg, int fid);

/*
 * for file _errors1.c
 */

int _erratoi(char *);

void print_error(infor_t *, char *);

int print_d(int, int);

char *convert_number(long int, int, int);

void remove_comments(char *);

/*
 * for file _exits.c
 */

char *_strncpy(char *, char *, int);

char *_strncat(char *, char *, int);

char *_strchr(char *, char);

/*
 * For file get getenv
 */

char **get_environ(infor_t *);

int _unsetenv(infor_t *, char *);

int _setenv(infor_t *, char *, char *);

/*
 * For file _getinfo.c
 */
void clear_info(infor_t *);

void set_info(infor_t *, char **);

void free_info(infor_t *, int);

/*
 * For file _getline.c
 */

ssize_t get_input(infor_t *);

int _getline(infor_t *, char **, size_t *);

void sigintHandler(int);

/*
 * For file _history.c
 */

char *get_history_file(infor_t *info);

int write_history(infor_t *infor);

int read_history(infor_t *infor);

int build_history_list(infor_t *infor, char *buff, int line_count);

int renumber_history(infor_t *infor);

/*
 * For file _lists.c
 */

list_t *add_node(list_t **, const char *, int);

list_t *add_node_end(list_t **, const char *, int);

size_t print_list_str(const list_t *);

int delete_node_at_index(list_t **, unsigned int);

void free_list(list_t **);

/* ================ Second Partner ========================= */

/*
 * For file _lists1.c
 */

size_t list_len(const list_t *);

char **list_to_strings(list_t *);

size_t print_list(const list_t *);

list_t *node_starts_with(list_t *, char *, char);

ssize_t get_node_index(list_t *, list_t *);

/* ========== main.c ======*/

/*
 * For file _memory.c
 */

int bfree(void **);

/*
 * For file _parser.c
 */

int is_cmd(infor_t *, char *);

char *dup_chars(char *, int, int);

char *find_path(infor_t *, char *, char *);

/*
 * For file _realloc.c
 */

char *_memset(char *, char, unsigned int);

void ffree(char **);

void *_realloc(void *, unsigned int, unsigned int);

/*
 * For file loophsh.c
 */

int loophsh(char **);

/*
 * For file _shloop.c
 */

int hsh(infor_t *, char **);

int find_builtin(infor_t *);

void find_cmd(infor_t *);

void fork_cmd(infor_t *);

/*
 * For file _string.c
 */

int _strlen(char *);

int _strcmp(char *, char *);

char *starts_with(const char *, const char *);

char *_strcat(char *, char *);

/*
 * For file _string1.c
 */

char *_strcpy(char *, char *);

char *_strdup(const char *);

void _puts(char *);

int _putchar(char);

/*
 * For file _tokenizer.c
 */

char **strtow(char *, char *);

char **strtow2(char *, char);

/*
 * For file _vars.c
 */

int is_chain(infor_t *, char *, size_t *);

void check_chain(infor_t *, char *, size_t *, size_t, size_t);

int replace_alias(infor_t *);

int replace_vars(infor_t *);

int rreplace_strring(char **, char *);
#endif
