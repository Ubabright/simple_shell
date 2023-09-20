#include "simple_shell.h"

/**
 * _shmemset - occupy memory with a specific byte number
 * @d: pointer to the memory location which is to be occupied
 * @r: byte value used to fill ‘*d
 * @num: the number of bytes to be occupied
 * Return: (d) a pointer to the memory area ‘d’ been occupied
 */
char *_shmemset(char *d, char r, unsigned int num)
{
	unsigned int z;

	for (z = 0; z < num; z++)
		d[z] = r;
	return (d);
}
/**
 * shfree - emptys memory populated by a string of strings
 * @ta: string of strings to be emptied
 */
void shfree(char **ta)
{
	char **b = ta;

	if (!ta)
		return;
	while (*ta)
		free(*ta++);
	free(b);
}

/**
 * _realloc - readjust size of memory that was allocated with malloc
 * @pt: pointer of former memory block, malloc allocated
 * @oldsiz: old block byte size
 * @nwsiz: new block byte size
 *
 * Return: pointer to altered memory
 */
void *_realloc(void *pt, unsigned int oldsiz, unsigned int nwsiz)
{
	char *u;

	if (!pt)
		return (malloc(nwsiz));
	if (!nwsiz)
		return (free(pt), NULL);
	if (nwsiz == oldsiz)
		return (pt);
	u = malloc(nwsiz);
	if (!u)
		return (NULL);
	oldsiz = oldsiz < nwsiz ? oldsiz : nwsiz;
	while (oldsiz--)
		u[oldsiz] = ((char *)pt)[oldsiz];
	free(pt);
	return (u);
}

