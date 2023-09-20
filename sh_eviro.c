#include "simple_shell.h"

/**
 * _shenvi - present environment is displayed
 * @dell: framework structure, for maintaining
 *          steady function prototype
 * Return: on success should return 0
 */

int _shenvi(dell_t *dell)
{
	prti_ltstri(dell->sh_env);
	return (0);
}

/**
 * _shgetenv - obtains value of an environment variable
 * @dell: framework structure, for maintaining
 *          steady function prototype
 * @nameof_env: name of env variable
 *
 * Return: appropriate value
 */
char *_shgetenv(dell_t *dell, const char *nameof_env)
{
	lt_t *cap = dell->sh_env;
	char *u;

	while (cap)
	{
		u = strt_with(cap->stri, nameof_env);
		if (u && *u)
			return (u);
		cap = cap->next_nod;
	}
	return (NULL);
}

/**
 * _setsshenvi - set a new environment var,
 *             or alters a present one
 * @dell: framework structure, for maintaining
 *          steady function prototype
 *  Return:  on success should return 0
 */
int _setsshenvi(dell_t *dell)
{
	if (dell->agc != 3)
	{
		_sheputs("number of arguement, not correct\n");
		return (1);
	}
	if (_shsetenv(dell, dell->str_argh[1], dell->str_argh[2]))
		return (0);
	return (1);
}

/**
 * _shunsetsenv -  cut off an environment var
 * @dell: framework structure, for maintaining
 *          steady function prototype
 * Return: should always return 0
 */
int _shunsetsenv(dell_t *dell)
{
	int z;

	if (dell->agc == 1)
	{
		_sheputs(" few arguments.\n");
		return (1);
	}
	for (z = 1; z <= dell->agc; z++)
		_unset_shenv(dell, dell->str_argh[z]);
	return (0);
}

/**
 * occupy_env_lt - occupy environment linked list
 * @dell: framework structure, for maintaining
 *          steady function prototype
 * Return: should always return 0
 */
int occupy_env_lt(dell_t *dell)
{
	lt_t *cap = NULL;
	size_t z;

	for (z = 0; environ[z]; z++)
		sh_nod_put_end(&cap, environ[z], 0);
	dell->sh_env = cap;
	return (0);
}
