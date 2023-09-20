#include "simple_shell.h"

/**
 * shbfree - frees a pointer and NULLs the address
 * @pt: address of the pointer to free
 *
 * Return: return 1 is successful empty, else ‘0’
 */
int shbfree(void **pt)
{
	if (pt && *pt)
	{
		free(*pt);
		*pt = NULL;
		return (1);
	}
	return (0);
}

