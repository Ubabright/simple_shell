#include "simple_shell.h"

/**
 * sh_active - denote if shell is in an interactive manner
 * @dell: dell_t structure address
 *
 * Return: if the shell is in interactive mode return 1, if not return 0
 */
int sh_active(dell_t *dell)
{
	return (isatty(STDIN_FILENO) && dell->readdirf <= 2);
}

/**
 * sh_stri_deli - makes sure that character is a delimeter
 * @ca: this is the char to be check
 * @stri_delim: the delimeter of string
 * Return: if true return 1, if false 0
 */
int sh_stri_deli(char ca, char *stri_delim)
{
	while (*stri_delim)
		if (*stri_delim++ == ca)
			return (1);
	return (0);
}

/**
 * shalpha - makes sure a character is alphabetic
 * @ca: the input character
 * Return: if ‘ca’ is alphabetic return 1, if ca is not return 0
 */

int shalpha(int ca)
{
	if ((ca >= 'A' && ca <= 'Z') || (ca >= 'a' && ca <= 'z'))
		return (1);
	else
		return (0);
}

/**
 *sh_stritoi - changes a string to integer form
 * @d: inputted string for conversion
 * Return: if there is no numerical digits in 'strg' return 1
 *					if not the converted number
 */

int sh_stritoi(char *d)
{
	int z, sgn = 1, flg = 0, outp;
	unsigned int reslt = 0;

	for (z = 0; flg != 2 && d[z] != '\0'; z++)
	{
		if (d[z] == '-')
			sgn *= -1;

		if (d[z] <= '9' && d[z] >= '0')
		{
			flg = 1;
			reslt *= 10;
			reslt += (d[z] - '0');
		}
		else if (flg == 1)
			flg = 2;
	}

	if (sgn == -1)
		outp = -reslt;
	else
		outp = reslt;

	return (outp);
}
