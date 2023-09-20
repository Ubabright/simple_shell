#include "simple_shell.h"

/**
 * sh_free_dell - initializes dell_t structure
 * @dell: location of structure
*/
void sh_free_dell(dell_t *dell)
{
	dell->arg_gt = NULL;
	dell->str_argh = NULL;
	dell->pre_path = NULL;
	dell->agc = 0;
}
/**
 * sh_set_dell - sets dell_t structure
 * @dell: location of structure instance
 * @arrv: the argument vector
 */
void sh_set_dell(dell_t *dell, char **arrv)
{
	int z = 0;

	dell->sh_fname = arrv[0];
	if (dell->arg_gt)
	{
		dell->str_argh = shstritow(dell->arg_gt, " \t");
		if (!dell->str_argh)
		{
			dell->str_argh = malloc(sizeof(char *) * 2);
			if (dell->str_argh)
			{
				dell->str_argh[0] = _strdup(dell->arg_gt);
				dell->str_argh[1] = NULL;
			}
		}
		for (z = 0; dell->str_argh && dell->str_argh[z]; z++)
			;
		dell->agc = z;
		ret_sh_alias(dell);
		ret_varis(dell);
	}
}

/**
 * free_dell - emptys dell_t structure fields
 * @dell: location of structure
 * @free_all: indicates true if empting all fields
 */
void free_dell(dell_t *dell, int free_all)
{
	shfree(dell->str_argh);
	dell->str_argh = NULL;
	dell->pre_path = NULL;
	if (free_all)
	{
		if (!dell->cmd_shbuff)
			free(dell->arg_gt);
		if (dell->sh_env)
			sh_frlt(&(dell->sh_env));
		if (dell->sh_history)
			sh_frlt(&(dell->sh_history));
		if (dell->sh_alias)
			sh_frlt(&(dell->sh_alias));
		shfree(dell->environ);
		dell->environ = NULL;
			shbfree((void **)dell->cmd_shbuff);
		if (dell->readdirf > 2)
			close(dell->readdirf);
		_shputchar(FLUSH_BUFF);
	}
}
