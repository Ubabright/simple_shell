#include "simple_shell.h"

/**
 *_shstrncpy - reprint a string
 *@locate: the location string to be reprinted to
 *@soce: string source
 *@num: the num of characters to be reprinted
 *Return: out-coming concatenated string
 */
char *_shstrncpy(char *locate, char *soce, int num)
{
	int z, o;
	char *d = locate;

	z = 0;
	while (soce[z] != '\0' && z < num - 1)
	{
		locate[z] = soce[z];
		z++;
	}
	if (z < num)
	{
		o = z;
		while (o < num)
		{
			locate[o] = '\0';
			o++;
		}
	}
	return (d);
}

/**
 **_shstrncat - joins together two strings
 *@locate: initial string
 *@soce: added string
 *@num: the total num of bytes to be involved
 *Return: the out-coming joined string
 */
char *_shstrncat(char *soce, char *locate, int num)
{
	int z, o;
	char *d = locate;

	z = 0;
	o = 0;
	while (locate[z] != '\0')
		z++;
	while (soce[o] != '\0' && o < num)
	{
		locate[z] = soce[o];
		z++;
		o++;
	}
	if (o < num)
		locate[z] = '\0';
	return (d);
}

/**
 **_shstrchr - discover a character in a string
 *@d: string to be discovered
 *@ca: the character to look for
 *Return: (d)  pointer to the memory location ‘d’
 */
char *_shstrchr(char *d, char ca)
{
	do {
		if (*d == ca)
			return (d);
	} while (*d++ != '\0');
	return (NULL);
}
