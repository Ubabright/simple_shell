#include "simple_shell.h"

/**
 * my_sh_cmd - determines if a file is an executable command
 * @dell: dell structure
 * @pre_path: process to the present file
 *
 * Return: if true return 1, else 0
 */
int my_sh_cmd(dell_t *dell, char *pre_path)
{
	struct stat sta;
	(void)dell;
	if (!pre_path || stat(pre_path, &sta))
		return (0);
	if (sta.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
/**
 * replica - replicate characters in a string
 * @pre_pathstri: input string(which contains chars)
 * @strndx: the initials index of replica characters
 * @spndx: the last index of replica characters
 *
 * Return: a pointer to a fresh created buffer
 */
char *replica(char *pre_pathstri, int strndx, int spndx)
{
	static char shbuff[1024];
	int z = 0, e = 0;

	for (e = 0, z = strndx; z < spndx; z++)
		if (pre_pathstri[z] != ':')
			shbuff[e++] = pre_pathstri[z];
		shbuff[e] = 0;
		return (shbuff);
}

/**
 * loc_pre_path - locates specific cmd in the PATH string
 * @dell: dell structure containings potential information
 * @pre_pathstri: the PATH string (search commens here)
 * @loc_cmd: command to locate
 *
 * Return: return command full path if found, NULL if not seen
 */
char *loc_pre_path(dell_t *dell, char *pre_pathstri, char *loc_cmd)
{
	int z = 0, pres_pst = 0;
	char *pre_path;

	if (!pre_pathstri)
		return (NULL);
	if ((_strlen(loc_cmd) > 2) && strt_with(loc_cmd, "./"))
	{
		if (my_sh_cmd(dell, loc_cmd))
			return (loc_cmd);
	}
	while (1)
	{
		if (!pre_pathstri[z] || pre_pathstri[z] == ':')
		{
			pre_path = replica(pre_pathstri, pres_pst, z);
			if (!*pre_path)
				_strcat(pre_path, loc_cmd);
			else
			{
				_strcat(pre_path, "/");
				_strcat(pre_path, loc_cmd);
			}
			if (my_sh_cmd(dell, pre_path))
				return (pre_path);
			if (!pre_pathstri[z])
				break;
			pres_pst = z;
		}
		z++;
		}
		return (NULL);
}



