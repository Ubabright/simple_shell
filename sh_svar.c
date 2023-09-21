#include "simple_shell.h"

/**
 * sh_is_chn - checks if present char in buffer is link delimeter
 * @dell: the framework structure
 * @shbuff: the buffer of the character
 * @u: is where currents position in shbuff is located
 *
 * Return:  if linked delimeter reeturn 1, else 0
 */
int sh_is_chn(dell_t *dell, char *shbuff, size_t *u)
{
	size_t o = *u;

	if (shbuff[o] == '|' && shbuff[o + 1] == '|')
	{
		shbuff[o] = 0;
		o++;
		dell->cmd_shbuff_type = SH_OR_CMD;
	}
	else if (shbuff[o] == '&' && shbuff[o + 1] == '&')
	{
		shbuff[o] = 0;
		o++;
		dell->cmd_shbuff_type = SH_AND_CMD;
	}
	else if (shbuff[o] == ';')
	{
		shbuff[o] = 0;
		dell->cmd_shbuff_type = SH_CHAIN_CMD;
	}
	else
		return (0);
	*u = o;
	return (1);
}

/**
 * sh_obs_chn - from previous status observes if we should continue chaining
 * @dell: the framework structure
 * @shbuff: character buffer
 * @u: where current position in shbuff is located
 * @z: the beginning point in ‘shbuff’
 * @lent: length of ‘shbuff’
 *
 * Return: void
 */
void sh_obs_chn(dell_t *dell, char *shbuff, size_t *u, size_t z, size_t lent)
{
	size_t o = *u;

	if (dell->cmd_shbuff_type == SH_AND_CMD)
	{
		if (dell->sh_status)
		{
			shbuff[z] = 0;
			o = lent;
		}
	}
	if (dell->cmd_shbuff_type == SH_OR_CMD)
	{
		if (!dell->sh_status)
		{
			shbuff[z] = 0;
			o = lent;
		}
	}
	*u = o;
}

/**
 * ret_sh_alias - puts an aliases in the tokenized string
 * @dell: the framework structure
 *
 * Return: return 1 if replacement occurs, else 0
 */
int ret_sh_alias(dell_t *dell)
{
	int z;
	lt_t *cap;
	char *u;

	for (z = 0; z < 10; z++)
	{
		cap = sh_nod_strt_with(dell->sh_alias, dell->str_argh[0], '=');
		if (!cap)
			return (0);
		free(dell->str_argh[0]);
		u = _shstrchr(cap->stri, '=');
		if (!u)
			return (0);
		u = _strdup(u + 1);
		if (!u)
			return (0);
		dell->str_argh[0] = u;
	}
	return (1);
}

/**
 * ret_varis - acts for variables in the tokenized string
 * @dell: the framework structure
 *
 * Return: if replacing is successful return 1, else 0
 */
int ret_varis(dell_t *dell)
{
		int z = 0;
		lt_t *cap;

		for (z = 0; dell->str_argh[z]; z++)
		{
			if (dell->str_argh[z][0] != '$' || !dell->str_argh[z][1])
				continue;

			if (!_shstrcmp(dell->str_argh[z], "$?"))
			{
				sh_rep_stri(&(dell->str_argh[z]),
					_strdup(sh_no_convt(dell->sh_status, 10, 0)));
				continue;
			}
			if (!_shstrcmp(dell->str_argh[z], "$$"))
			{
				sh_rep_stri(&(dell->str_argh[z]),
					_strdup(sh_no_convt(getpid(), 10, 0)));
				continue;
			}
			cap = sh_nod_strt_with(dell->sh_env, &dell->str_argh[z][1], '=');
			if (cap)
			{
				sh_rep_stri(&(dell->str_argh[z]),
					_strdup(_shstrchr(cap->stri, '=') + 1));
				continue;
			}
			sh_rep_stri(&dell->str_argh[z], _strdup(""));

		}
		return (0);
}

/**
 * sh_rep_stri - substitutes a former string with a new one
 * @oddstri: location of former string
 * @nwstri: present string location
 *
 * Return: if replaced successfully return 1, else 0
 */
int sh_rep_stri(char **oddstri, char *nwstri)
{
	free(*oddstri);
	*oddstri = nwstri;
	return (1);
}






