#include "simple_shell.h"


/**
 * _strlen - gives back string length
 * @d: given string which length is to be observed
 *
 * Return: digit denoting length of string
 */
int _strlen(char *d)
{
	int z = 0;

	if (!d)
		return (0);
	while (*d++)
		z++;
	return (z);
}
/**
 * _shstrcmp - takes on a lexicogarphic comparison of two strings
 * @d1: the first string to be compared
 * @d2: the second string to be compared
 *
 * Return: if s1 > s2 ‘positive’, if s1 < s2 negative,
 * 0 if both strings are equal
 */
int _shstrcmp(char *d1, char *d2)
{
	while (*d1 && *d2)
	{
		if (*d1 != *d2)
			return (*d1 - *d2);
			d1++;
			d2++;
	}
	if (*d1 == *d2)
		return (0);
	else
		return (*d1 < *d2 ? -1 : 1);
}

/**
  * strt_with - observes if needle begins with haystack
  * @hysak: string to observe inside
  * @nedl: substring to search
  *
  * Return: if found, location of next char of haystack or NULL
  */
char *strt_with(const char *hysak, const char *nedl)
{
	while (*nedl)
		if (*nedl++ != *hysak++)
			return (NULL);
		return ((char *)hysak);
}
/**
 * _strcat - join two strings together
 * @locate: the location buffer which the data will be added
 * @soce: the source buffer which contains the data to added
 *
 * Return: pointer to the target buffer
 */
char *_strcat(char *locate, char *soce)
{
	char *rtun = locate;

	while (*locate)
		locate++;
	while (*soce)
		*locate++ = *soce++;
	*locate = *soce;
	return (rtun);
}

