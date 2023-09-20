#include "simple_shell.h"

/**
 * insert_buf - buffers linked commands
 * @dell: framework structure
 * @shbuff: the buffer location
 * @lent: location of length variable
 *
 * Return: num of bytes read
 */
ssize_t insert_buf(dell_t *dell, char **shbuff, size_t *lent)
{
	ssize_t w = 0;
	size_t lent_u = 0;

	if (!*lent)
	{
		free(*shbuff);
		*shbuff = NULL;
		signal(SIGINT, sh_sginHandlers);
#if USED_GET_LINE
		w = getline(shbuff, &lent_u, stdin);
#else
		w = _shgetline(dell, shbuff, &lent_u);
#endif
		if (w > 0)
		{
			if ((*shbuff)[w - 1] == '\n')
			{
				(*shbuff)[w - 1] = '\0';
				w--;
			}
			dell->lines_flagged = 1;
			detach_cmts(*shbuff);
			sh_histo_list_bld(dell, *shbuff, dell->histo_cnt++);
			{
				*lent = w;
				dell->cmd_shbuff = shbuff;
			}
		}
	}
	return (w);
}

/**
 * sh_ret_input - collects a line, excluding newline
 * @info: framework structure
 *
 * Return: bytes read no.
 */
ssize_t sh_ret_input(dell_t *dell)
{
	static char *shbuff;
	static size_t z, o, lent;
	ssize_t w = 0;
	char **shbuff_u = &(dell->arg_gt), *u;

	_shputchar(FLUSH_BUFF);
	w = insert_buf(dell, &shbuff, &lent);
	if (w == -1)
		return (-1);
	if (lent)
	{
		o = z;
		u = shbuff + z;
		sh_obs_chn(dell, shbuff, &o, z, lent);
		while (o < lent)
		{
			if (sh_is_chn(dell, shbuff, &o))
				break;
			o++;
		}
		z = o + 1;
		if (z >= lent)
		{
			z = lent = 0;
			dell->cmd_shbuff_type = SH_NORM_CMD;
		}

		*shbuff_u = u;
		return (_strlen(u));
	}
	*shbuff_u = shbuff;
	return (w);
}

/**
 * buff_read - go through a buffer
 * @dell: framework structure
 * @shbuff: the buffer to go through
 * @z: the buffer size
 *
 * Return: the answer ‘w’
 */
ssize_t buff_read(dell_t *dell, char *shbuff, size_t *z)
{
	ssize_t w = 0;

	if (*z)
		return (0);
	w = read(dell->readdirf, shbuff, GET_BUFF_SIZE);
	if (w >= 0)
		*z = w;
	return (w);
}

/**
 * _shgetline - collects next line of input from STDIN
 * @dell: framework structure
 * @pt: pointer to buffer location, NULL or pre distributed
 * @leth: size of pre-distributed ‘pt’ buffer if not NULL
 *
 * Return: s
 */
int _shgetline(dell_t *dell, char **pt, size_t *leth)
{
	static char shbuff[GET_BUFF_SIZE];
	static size_t z, lent;
	size_t e;
	ssize_t w = 0, d = 0;
	char *u = NULL, *new_u = NULL, *ca;

	u = *pt;
	if (u && leth)
		d = *leth;
	if (z == lent)
		z = lent = 0;
	w = buff_read(dell, shbuff, &lent);
	if (w == -1 || (w == 0 && lent == 0))
		return (-1);
	ca = _shstrchr(shbuff + z, '\n');
	e = ca ? 1 + (unsigned int)(ca - shbuff) : lent;
	new_u = _realloc(u, d, d ? d + e : e + 1);
	if (!new_u)
		return (u ? free(u), -1 : -1);
	if (d)
		_shstrncat(new_u, shbuff + z, e - z);
	else
		_shstrncpy(new_u, shbuff + z, e - z + 1);
	d += e - z;
	z = e;
	u = new_u;
	if (leth)
		*leth = d;
	*pt = u;
	return (d);
}

/**
 * sh_sginHandlers - perform obstruction of ctrl-C
 * @sgno: digit of the signal
 *
 * Return: nothing
 */
void sh_sginHandlers(__attribute__((unused))int sgno)
{
	_shputs("\n");
	_shputs("$ ");
	_shputchar(FLUSH_BUFF);
}
