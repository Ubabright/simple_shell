#include "simple_shell.h"

/**
 * sh_get_hist - fetchs the file history
 * @dell: framework structure
 *
 * Return: given string containg file history
 */
char *sh_get_hist(dell_t *dell)
{
	char *shbuff, *dc;

	dc = _shgetenv(dell, "HOME=");
	if (!dc)
		return (NULL);
	shbuff = malloc(sizeof(char) * (_strlen(dc) + _strlen(FILE_HISTO) + 2));
	if (!shbuff)
		return (NULL);
	shbuff[0] = 0;
	_strcpy(shbuff, dc);
	_strcat(shbuff, "/");
	_strcat(shbuff, FILE_HISTO);
	return (shbuff);
}

/**
 * sh_wri_histo - makes a file, or modifies to an existing file
 * @dell: the framework structure
 *
 * Return: if successful 1, otherwise -1
 */
int sh_wri_histo(dell_t *dell)
{
	ssize_t dirf;
	char *filenm = sh_get_hist(dell);
	lt_t *cap = NULL;

	if (!filenm)
		return (-1);
	dirf = open(filenm, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filenm);
	if (dirf == -1)
		return (-1);
	for (cap = dell->sh_history; cap; cap = cap->next_nod)
	{
		_shputsdirf(cap->stri, dirf);
		_shputdirf('\n', dirf);
	}
	_shputdirf(FLUSH_BUFF, dirf);
	close(dirf);
	return (1);
}

/**
 * sh_rd_histo - fetch information history from a file
 * @dell: the framework structure
 *
 * Return: if successful return the ‘history count’, else ‘0’
 */
int sh_rd_histo(dell_t *dell)
{
	int z, lat = 0, linecnt = 0;
	ssize_t dirf, readlent, fsiz = 0;
	struct stat sta;
	char *shbuff = NULL, *filenm = sh_get_hist(dell);

	if (!filenm)
		return (0);
	dirf = open(filenm, O_RDONLY);
	free(filenm);
	if (dirf == -1)
		return (0);
	if (!fstat(dirf, &sta))
		fsiz = sta.st_size;
	if (fsiz < 2)
		return (0);
	shbuff = malloc(sizeof(char) * (fsiz + 1));
	if (!shbuff)
		return (0);
	readlent = read(dirf, shbuff, fsiz);
	shbuff[fsiz] = 0;
	if (readlent <= 0)
		return (free(shbuff), 0);
	close(dirf);
	for (z = 0; z < fsiz; z++)
		if (shbuff[z] == '\n')
		{
			shbuff[z] = 0;
			sh_histo_list_bld(dell, shbuff + lat, linecnt++);
			lat = z + 1;
		}
	if (lat != z)
		sh_histo_list_bld(dell, shbuff + lat, linecnt++);
	free(shbuff);
	dell->histo_cnt = linecnt;
	while (dell->histo_cnt-- >= MAX_HISTO)
		sh_del_node_at_idx(&(dell->sh_history), 0);
	sh_reno_histo(dell);
	return (dell->histo_cnt);
}

/**
 * sh_histo_list_bld - puts an entry to a linked list history
 * @dell: structure containing framework, used to maintain
 * @shbuff: present buffer
 * @linecnt: line count of the  history
 *
 * Return: should always return 0
 */
int sh_histo_list_bld(dell_t *dell, char *shbuff, int linecnt)
{
	lt_t *cap = NULL;

	if (dell->sh_history)
		cap = dell->sh_history;
	sh_nod_put_end(&cap, shbuff, linecnt);
	if (!dell->sh_history)
		dell->sh_history = cap;
	return (0);
}
/**
 * sh_reno_histo - rearranges history linked list after alters
 * @dell: structure containing framework, used to position
 *
 * Return: the present histo_cnt
 */
int sh_reno_histo(dell_t *dell)
{
	lt_t *cap = dell->sh_history;
	int z = 0;

	while (cap)
	{
		cap->no = z++;
		cap = cap->next_nod;
	}
	return (dell->histo_cnt = z);
}
