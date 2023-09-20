#include "simple_shell.h"

/**
 * _sheputs - showcase an inputted string
 * @stri: string to be showcased
 *
 * Return: no exact return value
 */
void _sheputs(char *stri)
{
	int z = 0;

	if (!stri)
		return;
	while (stri[z] != '\0')
	{
		_sheputchar(stri[z]);
		z++;
	}
}

/**
 * _sheputchar - input character ca to stderr
 * @ca: the character to be printed
 *
 * Return: if successful 1
 * on error, -1 is returned, and variable ‘errno’ is set correctly
 */
int _sheputchar(char ca)
{
	static int z;
	static char shbuff[INPUT_BUF_SIZE];

	if (z >= INPUT_BUF_SIZE || ca == FLUSH_BUFF)
	{
		write(2, shbuff, z);
		z = 0;
	}
	if (ca != FLUSH_BUFF)
		shbuff[z++] = ca;
	return (1);
}


/**
 * _shputdirf - inputs character ‘ca’
 *			to a descriptor file ‘dirf’
 * @ca: character to be printed
 * @dirf: the descriptor file to input to
 *
 * Return: if successful 1
 * on error, -1 is returned, and variable ‘errno’ is set correctly
 */
int _shputdirf(char ca, int dirf)
{
	static int z;
	static char shbuff[INPUT_BUF_SIZE];

	if (z >= INPUT_BUF_SIZE || ca == FLUSH_BUFF)
	{
		write(dirf, shbuff, z);
		z = 0;
	}
	if (ca != FLUSH_BUFF)
		shbuff[z++] = ca;
	return (1);
}

/**
 * _shputsdirf - display an input string to given descriptor file
 * @stri: string to be outputted
 * @dirf: the descriptor file to input to
 *
 * Return: amount of chars inputted
 */
int _shputsdirf(char *stri, int dirf)
{
	int z = 0;

	if (!stri)
		return (0);
	while (*stri)
	{
		z += _shputdirf(*stri++, dirf);
	}
	return (z);
}
