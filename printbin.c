#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "main.h"


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
	if (q == 0)
		return (write(1, "0", 1));
	/*find the length of the binary form of the int*/
	for (i = 0; q != 0; i++)
	{
		q = q / 2;
		bin_len++;
	}
	ptc = malloc(sizeof(char) * bin_len + 1);
	if (ptc == NULL)
	{
		return (0);
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
			return (bytes_count);
		bytes_count += bytes_written;
	}
	return (bytes_count);
}
