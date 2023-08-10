#include "shell.h"

/**
 * _erratoi - A function that converts or changes a str to an int.
 * @x: the string to be changed or converted
 * Return: 0 for no numbers in string or -1 otherwise(error)
 */

int _erratoi(char *x)

{
	int d = 0;
	unsigned long int answer = 0;

	if (*x == '+')
	{
	x++;  /* TODO: why does this make main return 255? */
	}
	for (d = 0;  x[d] != '\0'; d++)
	{
	if (x[d] >= '0' && x[d] <= '9')
	{
	answer *= 10;
	answer += (x[d] - '0');
	if (answer > INT_MAX)
	{
	return (-1);
	}
	}
	else
	{
	return (-1);
	}
	}
	return (answer);
}

/**
 * print_error - A program that prints an error message
 * @infor: the return infor struct and parameter
 * @strg: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 * -1 on error
 */

void print_error(infor_t *infor, char *strg)

{
	_eputs(infor->flname);
	_eputs(": ");
	print_d(infor->line_counts, STDERR_FILENO);
	_eputs(": ");
	_eputs(infor->argv[0]);
	_eputs(": ");
	_eputs(strg);
}

/**
 * print_d - A function that prints a decimal (int) to number (base_ 10)
 * @inputs: the input number
 * @fid: the filedescriptor to be written to
 * Return: number of characters printed
 */

int print_d(int inputs, int fid)

{
	int (*__putchar)(char) = _putchar;
	int d, counts = 0;
	unsigned int _abs__, current_num;

	if (fid == STDERR_FILENO)
	{
	__putchar = _eputchar;
	}
	if (inputs < 0)
	{
	_abs__ = -inputs;
	__putchar('-');
	counts++;
	}
	else
		_abs__ = inputs;
	current_num = _abs__;
	for (d = 1000000000; d > 1; d /= 10)
	{
	if (_abs__ / d)
	{
	__putchar('0' + current_num / d);
	counts++;
	}
	current_num %= d;
	}
	__putchar('0' + current_num);
	counts++;
	return (counts);
}

/**
 * convert_number - A function that converter functions,
 * a clone of itoa.
 * @numb: the number
 * @base__: the base
 * @flgs: the argument flags
 * Return: string(successful)
 */

char *convert_number(long int numb, int base__, int flgs)

{
	static char *arry;
	static char buffer[50];
	char sign_ = 0;
	char *ptrs;
	unsigned long nm = numb;

	if (!(flgs & CONVERT_UNSIGNED) && numb < 0)
	{
	nm = -numb;
	sign_ = '-';
	}
	arry = flgs & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptrs = &buffer[49];
	*ptrs = '\0';
	do {
	*--ptrs = arry[nm % base__];
	nm /= base__;
	} while (nm != 0);
	if (sign_)
	{
	*--ptrs = sign_;
	}
	return (ptrs);
}

/**
 * remove_comments - A function that replaces 1st instance of '#'
 * with '\0'
 * @buff: the address of the string to be modify
 * Return: 0 (Always)
 */

void remove_comments(char *buff)

{
	int d;

	for (d = 0; buff[d] != '\0'; d++)
	{
	if (buff[d] == '#' && (!d || buff[d - 1] == ' '))
	{
	buff[d] = '\0';
	break;
	}
	}
}

