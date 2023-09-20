#include "simple_shell.h"

/**
 * _get_shenviron - gets a copy arrays of string, of env
 * @dell: framework structure, for maintaining
 *          steady function prototype
 * Return: should always be 0
 */
char **_get_shenviron(dell_t *dell)
{
	if (!dell->environ || dell->sh_env_changed)
	{
		dell->environ = sh_lt_to_strn(dell->sh_env);
		dell->sh_env_changed = 0;
	}
	return (dell->environ);
}

/**
 * _unset_shenv - discard an environ variable
 * @dell: framework structure, for maintaining
 *          steady function prototype
 *  Return: return 1 if discarded, else 0
 * @vari: the environ variable property string
 */
int _unset_shenv(dell_t *dell, char *vari)
{
	lt_t *cap = dell->sh_env;
	size_t z = 0;
	char *u;

	if (!cap || !vari)
		return (0);
	while (cap)
	{
		u = strt_with(cap->stri, vari);
		if (u && *u == '=')
		{
			dell->sh_env_changed = sh_del_node_at_idx(&(dell->sh_env), z);
			z = 0;
			cap = dell->sh_env;
			continue;
		}
		cap = cap->next_nod;
		z++;
	}
	return (dell->sh_env_changed);
}

/**
 * _shsetenv - forms a new environment variable,
 *             or alter present one
 * @dell: framework structure, for maintaining
 *          steady function prototype
 * @vari: the environ variable property string
 * @va: the environ variable string value
 *  Return: should always return 0
 */
int _shsetenv(dell_t *dell, char *vari, char *va)
{
	char *shbuff = NULL;
	lt_t *cap;
	char *u;

	if (!vari || !va)
		return (0);
	shbuff = malloc(_strlen(vari) + _strlen(va) + 2);
	if (!shbuff)

		return (1);
	_strcpy(shbuff, vari);
	_strcat(shbuff, "=");
	_strcat(shbuff, va);
	cap = dell->sh_env;
	while (cap)
	{
		u = strt_with(cap->stri, vari);
		if (u && *u == '=')
		{
			free(cap->stri);
			cap->stri = shbuff;
			dell->sh_env_changed = 1;
			return (0);
		}
		cap = cap->next_nod;
	}
	sh_nod_put_end(&(dell->sh_env), shbuff, 0);
	free(shbuff);
	dell->sh_env_changed = 1;
	return (0);
}
