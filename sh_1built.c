#include "simple_shell.h"

/**
 * _shhistory - shows the history in a command by line, format
 *              with line digits, beginning from 0
 * @dell: a structure containing our framework. used to maintain
 * steady function prototype
 *  Return: should always return 0
 */
int _shhistory(dell_t *dell)
{
	prti_lt(dell->sh_history);
	return (0);
}

/**
 * uset_alias - arrange an alias to a string
 * @dell: framework structure
 * @stri: alias of the string
 *
 * Return: on success should always return 0, on error 1
 */
int uset_alias(dell_t *dell, char *stri)
{
	char *u, ca;
	int rtun;

	u = _shstrchr(stri, '=');
	if (!u)
		return (1);

	ca = *u;
	*u = 0;
	rtun = sh_del_node_at_idx(&(dell->sh_alias),
			shget_ndx_nod(dell->sh_alias, sh_nod_strt_with(dell->sh_alias, stri, -1)));
	*u = ca;
	return (rtun);
}

/**
 * sets_alias - arrange an alias to a string
 * @dell: framework structure
 * @stri: alias of the string
 *
 * Return: on success should always return 0, on error 1
 */

int sets_alias(dell_t *dell, char *stri)
{
	char *u;

	u = _shstrchr(stri, '=');
	if (!u)
		return (1);
	if (!*++u)
		return (uset_alias(dell, stri));
	uset_alias(dell, stri);
	return (sh_nod_put_end(&(dell->sh_alias), stri, 0) == NULL);
}

/**
 * sh_print_alias - displays an alias str
 * @cap: this is node of the alias
 *
 * Return: on success should return 0, on error 1
 */
int sh_print_alias(lt_t *cap)
{
	char *u = NULL, *b = NULL;

	if (cap)
	{
		u = _shstrchr(cap->stri, '=');
		for (b = cap->stri; b <= u; b++)
			_shputchar(*b);
		_shputchar('\'');
		_shputs(u + 1);
		_shputs("'\n");
		return (0);
	}
	return (1);
}

/**
 * _shalias - acts like the alias builtin (man alias)
 * @dell: framework structure, for maintaining
 *          constant function prototype.
 *  Return: on success should return 0
 */
int _shalias(dell_t *dell)
{
	int z = 0;
	char *u = NULL;
	lt_t *cap = NULL;

	if (dell->agc == 1)
	{
		cap = dell->sh_alias;
		while (cap)
		{
			sh_print_alias(cap);
			cap = cap->next_nod;
		}
		return (0);
	}
	for (z = 1; dell->str_argh[z]; z++)
	{
		u = _shstrchr(dell->str_argh[z], '=');
		if (u)
			sets_alias(dell, dell->str_argh[z]);
		else
			sh_print_alias(sh_nod_strt_with(dell->sh_alias, dell->str_argh[z], '='));
	}
	return (0);
}
