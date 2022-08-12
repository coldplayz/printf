#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "main.h"


/**
 * printptr - prints an address in lowercase hex.
 * @p: the address to print.
 *
 * Return: the number of characters printed in an array of int.
 */
int *printptr(void *p)
{
	long int q = (long int)p, rem = 0, diff = 0;
	int i, hex_len = 0, ai[2] = {6, 0}, *pti = ai;
	char *ptc, *str = "abcdef";

	if (p == 0)
	{
		write(1, "(nil)", 6);
		return (pti);
	}
	/*find the length of the binary form of the int*/
	for (hex_len = 0; q != 0; hex_len++)
	{
		q = q / 16;
	}
	ptc = malloc(sizeof(char) * hex_len + 3);
	if (ptc == NULL)
		return (0);

	q = (long int)p;
	/*populate the ptc's malloc'd array*/
	/*with digits of hex, in reversed order*/
	for (i = 0; q != 0; i++)
	{
		rem = q % 16;
		diff = rem - 10;
		if (diff >= 0 && diff <= 5)
			ptc[i] = str[diff];
		else
			ptc[i] = rem + '0';
		q /= 16;
	}
	ptc[i] = 'x';
	ptc[i + 1] = '0';
	ai[0] = 0;
	/*print the ptc array, in reverse*/
	for (i = (hex_len + 1); i >= 0; i--)
	{
		ai[0] += write(1, (ptc + i), 1);
	}
	return (pti);
}
