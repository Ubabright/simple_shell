#include "simple_shell.h"

/**
 * lt_lent - estimates length of linked list
 * @l: a first node pointer
 *
 * Return: list size
 */
size_t lt_lent(const lt_t *l)
{
	size_t z = 0;

	while (l)
	{
		l = l->next_nod;
		z++;
	}
	return (z);
}
/**
 * sh_lt_to_strn - alters the list of ‘stri’ parameter
 *		into an array of strings
 * @top_nod: pointer to top node
 *
 * Return: array of strings
 */
char **sh_lt_to_strn(lt_t *top_nod)
{
	lt_t *cap = top_nod;
	size_t z = lt_lent(top_nod), o;
	char **stris;
	char *stri;

	if (!top_nod || !z)
		return (NULL);
	stris = malloc(sizeof(char *) * (z + 1));
	if (!stris)
		return (NULL);
	for (z = 0; cap; cap = cap->next_nod, z++)
	{
		stri = malloc(_strlen(cap->stri) + 1);
		if (!stri)
		{
			for (o = 0; o < z; o++)
				free(stris[o]);
			free(stris);
			return (NULL);
		}
		stri = _strcpy(stri, cap->stri);
		stris[z] = stri;
	}
	stris[z] = NULL;
	return (stris);
}

/**
 * prti_lt - displays all component of a lt_t linked list
 * @l: first node pointer
 *
 * Return: list of size
 */
size_t prti_lt(const lt_t *l)
{
	size_t z = 0;

	while (l)
	{
		_shputs(sh_no_convt(l->no, 10, 0));
		_shputchar(':');
		_shputchar(' ');
		_shputs(l->stri ? l->stri : "(nil)");
		_shputs("\n");
		l = l->next_nod;
		z++;
	}
	return (z);
}
/**
 * sh_nod_strt_with - identify node if string begins with prefix
 * @node: the list top pointer
 * @idstri: to be matched string as prefix
 * @ca: following character to match after prefix
 * @cap: a pointer to a node
 *
 * Return: identical node or if not found ’null’
 */
lt_t *sh_nod_strt_with(lt_t *cap, char *idstri, char ca)
{
	char *u = NULL;

	while (cap)
	{
		u = strt_with(cap->stri, idstri);
		if (u && ((ca == -1) || (*u == ca)))
			return (cap);
		cap = cap->next_nod;
	}
	return (NULL);
}

/**
 * shget_ndx_nod - fetch index of the node
 * @top_nod: points to the list top
 * @node: the node pointer
 * @cap: a pointer to a node
 * Return: returns the node index, else -1
 */
ssize_t shget_ndx_nod(lt_t *top_nod, lt_t *cap)
{
	size_t z = 0;

	while (top_nod)
	{
		if (top_nod == cap)
			return (z);
		top_nod = top_nod->next_nod;
		z++;
	}
	return (-1);
}



























