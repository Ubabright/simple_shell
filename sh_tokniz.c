#include "simple_shell.h"

/**
 * shstritow - shares a string into more words.
 * delimiter repeated are left
 * @stri: string to be divided (input string)
 * @del_stri: delimeter string for spiliting
 * Return: a pointer to strings array, or on failure NULL
 */
char **shstritow(char *stri, char *del_stri)
{
	int z, o, e, y, wrdsn = 0;
	char **d;

	if (stri == NULL || stri[0] == 0)
		return (NULL);
	if (!del_stri)
		del_stri = "";
	for (z = 0; stri[z] != '\0'; z++)
		if (!sh_stri_deli(stri[z], del_stri) && (sh_stri_deli(stri[z + 1],
			del_stri) || !stri[z + 1]))
			wrdsn++;
		if (wrdsn == 0)
			return (NULL);
		d = malloc((1 + wrdsn) * sizeof(char *));
		if (!d)
			return (NULL);
		for (z = 0, o = 0; o < wrdsn; o++)
		{
			while (sh_stri_deli(stri[z], del_stri))
				z++;
			e = 0;
			while (!sh_stri_deli(stri[z + e], del_stri) && stri[z + e])
				e++;
			d[o] = malloc((e + 1) * sizeof(char));
			if (!d[o])
			{
			for (e = 0; e < o; e++)
				free(d[e]);
			free(d);
			return (NULL);
			}
			for (y = 0; y < e; y++)
				d[o][y] = stri[z++];
			d[o][y] = 0;
		}
		d[o] = NULL;
		return (d);
}

/**
 * shstritow2 - shares a string into more words
 * @stri: to be divided string
 * @del_stri: the delimeter, this shows where separation occurs
 * Return: a pointer to strings array, or on failure NULL
 */
char **shstritow2(char *stri, char del_stri)
{
		int z, o, e, y, wrdsn = 0;
		char **d;

		if (stri == NULL || stri[0] == 0)
			return (NULL);
		for (z = 0; stri[z] != '\0'; z++)
			if ((stri[z] != del_stri && stri[z + 1] == del_stri) ||
				(stri[z] != del_stri && !stri[z + 1]) || stri[z + 1] == del_stri)
				wrdsn++;
		if (wrdsn == 0)
			return (NULL);
		d = malloc((1 + wrdsn) * sizeof(char *));
		if (!d)
			return (NULL);
		for (z = 0, o = 0; o < wrdsn; o++)
		{
			while (stri[z] == del_stri && stri[z] != del_stri)
				z++;
			e = 0;
			while (stri[z + e] != del_stri && stri[z + e] && stri[z + e] != del_stri)
				e++;
			d[o] = malloc((e + 1) * sizeof(char));
			if (!d[o])
			{
				for (e = 0; e < o; e++)
					free(d[e]);
				free(d);
				return (NULL);
			}
			for (y = 0; y < e; y++)
				d[o][y] = stri[z++];
			d[o][y] = 0;
		}
		d[o] = NULL;
		return (d);
}











