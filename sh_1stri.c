#include "simple_shell.h"


/**
 * _strcpy - replicates a string
 * @locate: location of buffer
 * @soce: the buffer source
 *
 * Return: pointer to location buffer
 */
char *_strcpy(char *locate, char *soce)
{
	int z = 0;

	if (locate == soce || soce == 0)
		return (locate);
	while (soce[z])
	{
		locate[z] = soce[z];
		z++;
	}
	locate[z] = 0;
	return (locate);
}
/**
 * _strdup - duplicates the contents in a string
 * @stri: the replica string
 *
 * Return: pointer to the replicated string
 */
char *_strdup(const char *stri)
{
	int leth = 0;
	char *rtun;

	if (stri == NULL)
		return (NULL);
	while (*stri++)
		leth++;
	rtun = malloc(sizeof(char) * (leth + 1));
	if (!rtun)
		return (NULL);
	for (leth++; leth--;)
		rtun[leth] = *--stri;
	return (rtun);
}

/**
 * _shputs - show an input string
 * @stri: the string to be displayed
 *
 * Return: NONE
 */
void _shputs(char *stri)
{
	int z = 0;

	if (!stri)
		return;
	while (stri[z] != '\0')
	{
		_shputchar(stri[z]);
		z++;
	}
}

/**
 * _shputchar - output the character ‘ca’ to standard output
 * @ca: The character to printed
 *
 * Return: if successfully return 1
 * On error, return -1, and set errno properly
 */
int _shputchar(char ca)
{
	static int z;
	static char shbuff[INPUT_BUF_SIZE];

	if (ca == FLUSH_BUFF || z >= INPUT_BUF_SIZE)
	{
		write(1, shbuff, z);
		z = 0;
	}
	if (ca != FLUSH_BUFF)
	{
		shbuff[z++] = ca;
	}
		return (1);
}





