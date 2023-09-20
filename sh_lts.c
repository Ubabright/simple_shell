#include "simple_shell.h"

/**
 * nod_put - puts node to the beginning of the list
 * @top_nod: pointer location to head node
 * @stri: new node string area
 * @no: node index used by history
 *
 * Return: list size
*/
lt_t *nod_put(lt_t **top_nod, const char *stri, int no)
{
	lt_t *nw_top;

	if (!top_nod)
		return (NULL);
	nw_top = malloc(sizeof(lt_t));
	if (!nw_top)
		return (NULL);
	_shmemset((void *)nw_top, 0, sizeof(lt_t));
	nw_top->no = no;
	if (stri)
	{
		nw_top->stri = _strdup(stri);
		if (!nw_top->stri)
		{
			free(nw_top);
			return (NULL);
		}
	}
	nw_top->next_nod = *top_nod;
	*top_nod = nw_top;
	return (nw_top);
}

/**
 * sh_nod_put_end - puts node to the last of the list
 * @top_nod: pointer location to top node
 * @stri: area of string node
 * @no: index of node utilized by history
 *
 * Return: list size
 */
lt_t *sh_nod_put_end(lt_t **top_nod, const char *stri, int no)
{
	lt_t *nw_nod, *cap;

	if (!top_nod)
		return (NULL);
	cap = *top_nod;
	nw_nod = malloc(sizeof(lt_t));
	if (!nw_nod)
		return (NULL);
	_shmemset((void *)nw_nod, 0, sizeof(lt_t));
	nw_nod->no = no;
	if (stri)
	{
		nw_nod->stri = _strdup(stri);
		if (!nw_nod->stri)
		{
			free(nw_nod);
			return (NULL);
		}
	}
	if (cap)
	{
		while (cap->next_nod)
			cap = cap->next_nod;
		cap->next_nod = nw_nod;
	}
	else
		*top_nod = nw_nod;
	return (nw_nod);
}

/**
 * prti_ltstri - displays the stri element of a list_t linked list
 * @l: first node pointer
 *
 * Return: list size
 */
size_t prti_ltstri(const lt_t *l)
{
	size_t z = 0;

	while (l)
	{
		_shputs(l->stri ? l->stri : "(nil)");
		_shputs("\n");
		l = l->next_nod;
		z++;
	}
	return (z);
}
/**
 * sh_del_node_at_idx - removes a node at stated index
 * @top_nod: initials node pointer location
 * @ndx: to be delete node index
 *
 * Return: if successful 1, else 0
 */
int sh_del_node_at_idx(lt_t **top_nod, unsigned int ndx)
{
	lt_t *cap, *form_nod;
	unsigned int z = 0;

	if (!top_nod || !*top_nod)
		return (0);
	if (!ndx)
	{
		cap = *top_nod;
		*top_nod = (*top_nod)->next_nod;
		free(cap->stri);
		free(cap);
		return (1);
	}
	cap = *top_nod;
	while (cap)
	{
		if (z == ndx)
		{
			form_nod->next_nod = cap->next_nod;
			free(cap->stri);
			free(cap);
			return (1);
		}
		z++;
		form_nod = cap;
		cap = cap->next_nod;
	}
	return (0);
}
/**
 * sh_frlt - lets go of all nodes in a list
 * @top_pt: location of pointer to top node
 *
 * Return: nothing
 */
void sh_frlt(lt_t **top_pt)
{
	lt_t *cap, *nx_nod, *top_nod;

	if (!top_pt || !*top_pt)
		return;
	top_nod = *top_pt;
	cap = top_nod;
	while (cap)
	{
		nx_nod = cap->next_nod;
		free(cap->stri);
		free(cap);
		cap = nx_nod;
	}
	*top_pt = NULL;
}


