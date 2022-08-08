#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "main.h"

/**
 * _printf - produces output according to a format
 *  @format: a string containing normal
 *  sequence(s) of characters to print as-is, and
 *  special character sequence(s) to determine how to print the next arguments.
 *
 *  Return: the number of characters printed,
 *  excluding the string-terminating null character
 */
int _printf(const char *format, ...)
{
	int i, bytes_written = 0;
	va_list ap;

	va_start(ap, format);	/*initialize argument pointer*/
	for (i = 0; format[i]; i++)
	{
		if (format[i] == '%')	/*when a % character is encountered*/
		{
			/*ret stores the number of bytes*/
			/*written by the call to print_any2*/
			switch (format[++i])
			{
				case 'c':
					bytes_written += printc(va_arg(ap, int));
					break;
				case 's':
					bytes_written += prints(va_arg(ap, char *));
					break;
				case '%':
					bytes_written += printp();
					break;
				case 'b':
					bytes_written += printbin(va_arg(ap, unsigned int));
					break;
				default:
					bytes_written += write(1, (format + i), 1);
			}
		}
		else
		{
			bytes_written = write(1, (format + i), 1);
		}
	}
	va_end(ap);
	return (bytes_written);
}



/**
 * c2s - converts a character constant, or single-digit integer, to a string.
 * @c: a char
 * @i: an int
 * @flag: an int indicating whether the
 * output is from a char (0), or from an int (1).
 *
 * Return: a pointer to a string
 */
char *c2s(char c, int i, int flag)
{
	char *ptc;
	char arr[2];

	ptc = arr;
	if (flag)		/*for when the output string is to be from an integer*/
	{
		(void)c;	/*declare the variable, c, as unsused*/
		ptc[0] = i + '0';
		ptc[1] = '\0';
	}
	else
	{
		(void)i;
		ptc[0] = c;
		ptc[1] = '\0';
	}

	return (ptc);
}



/**
 * _strlen - returns the length of a string
 * @s: pointer to char type
 *
 * Return: an integer length of the argument
 */
int _strlen(char *s)
{
	int len, shift = 0;

	for (len = 0; *(s + shift);)
	{
		len++;
		shift++;
	}

	return (len);
}



/**
 * printbin - prints an unsigned int in binary.
 * @n: the unsigned integer to print.
 *
 * Return: the number of characters printed, or -1 if write error.
 */
int printbin(unsigned int n)
{
	unsigned int i, q = 1, bin_len = 0;
	int bytes_written = 0, bytes_count = 0;
	char *ptc;

	q = n;
	/*find the length of the binary form of the int*/
	for (i = 0; q != 0; i++)
	{
		q = q / 2;
		bin_len++;
	}
	ptc = malloc(sizeof(char) * bin_len + 1);
	if (ptc == NULL)
	{
		write(1, "?", 1);
		exit(EXIT_FAILURE);
	}

	q = n;
	/*populate the ptc's malloc'd array*/
	/*with digits of binary, in reversed order*/
	for (i = 0; q != 0; i++)
	{
		ptc[i] = (q % 2) + '0';
		q /= 2;
	}

	/*print the ptc array, in reverse*/
	for (i = (bin_len - 1); i >= 0; i--)
	{
		bytes_written = write(1, (ptc + i), 1);
		if (bytes_written == -1)
			return (-1);
		bytes_count += bytes_written;
	}
	return (bytes_count);
}


/**
 * printc - prints a char
 * @arg: the char to print
 *
 * Return: the number of bytes written/printed to STDOUT
 */
int printc(char arg)
{
	int bytes_written;

	bytes_written = 0;
	write(1, c2s(arg, 0, 0), 1);
	bytes_written += 1;

	return (bytes_written);
}


/**
 * printp - prints the percentage character (%).
 *
 * Return: the number of bytes written/printed to STDOUT
 */
int printp(void)
{
	int bytes_written;

	bytes_written = 0;

	bytes_written = write(1, "%", 1);

	if (bytes_written == -1)
	{
		return (-1);
	}

	return (bytes_written);
}


/**
 * prints - prints the string s
 * @s: a pointer to the string to print
 *
 * Return: the number of bytes written/printed to STDOUT
 */
int prints(char *s)
{
	int  bytes_written;

	bytes_written = 0;
	bytes_written = write(1, s, _strlen(s));
	if (bytes_written == -1)
	{
		return (-1);
	}

	return (bytes_written);
}
