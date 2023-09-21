#include "simple_shell.h"

/**
 * ssh - central shell loop
 * @dell: framework and return framework structure
 * @arrv: from main() function the ‘argument vector’
 *
 * Return: if successful 0, if there’s error 1, or error code
 */
int ssh(dell_t *dell, char **arrv)
{
	ssize_t w = 0;
	int inbuilt_rtun = 0;

	while (w != -1 && inbuilt_rtun != -2)
	{
		sh_free_dell(dell);
		if (sh_active(dell))
			_shputs("$ ");
		_sheputchar(FLUSH_BUFF);
		w = sh_ret_input(dell);
		if (w != -1)
		{
			sh_set_dell(dell, arrv);
			inbuilt_rtun = loc_inbuilt(dell);
			if (inbuilt_rtun == -1)
				fd_loc_cmd(dell);
		}
		else if (sh_active(dell))
			_shputchar('\n');
		free_dell(dell, 0);
		}
			sh_wri_histo(dell);
		free_dell(dell, 1);
		if (!sh_active(dell) && dell->sh_status)
			exit(dell->sh_status);
		if (inbuilt_rtun == -2)
		{
			if (dell->digit_err == -1)
				exit(dell->sh_status);
			exit(dell->digit_err);
		}
		return (inbuilt_rtun);
}

/**
  * loc_inbuilt - finds an inbuilt command
  * @dell: framework and return framework structure
  *
  * Return: if in-built not found -1,
  * if in-built worked properly, return 0,
  * if in-built found but failed, return 1,
  *if in-built signals exit(), return 2
 */
int loc_inbuilt(dell_t *dell)
{
	int z, inbuilt_rtun = -1;
	inbuilt_tab inbuildtab[] = {
		{"exit", _shexit},
		{"env", _shenvi},
		{"help", _shhelp},
		{"history", _shhistory},
		{"setenv", _setsshenvi},
		{"unsetenv", _shunsetsenv},
		{"cd", _shcd},
		{"alias", _shalias},
		{NULL, NULL}
	};
	for (z = 0; inbuildtab[z].builtin_typ; z++)
		if (_shstrcmp(dell->str_argh[0], inbuildtab[z].builtin_typ) == 0)
		{
			dell->cnt_error++;
			inbuilt_rtun = inbuildtab[z].builtin_fun(dell);
			break;
		}
	return (inbuilt_rtun);
}

/**
 * fd_loc_cmd - locates a command in PATH environment
 * @dell: framework and return framework structure
 *
 * Return: nothing
 */
void fd_loc_cmd(dell_t *dell)
{
	char *pre_path = NULL;
	int z, e;

	dell->pre_path = dell->str_argh[0];

	if (dell->lines_flagged == 1)
	{
		dell->cnt_error++;
		dell->lines_flagged = 0;
	}
	for (z = 0, e = 0; dell->arg_gt[z]; z++)
	{
		if (!sh_stri_deli(dell->arg_gt[z], " \t\n"))
			e++;
	}
		if (!e)
			return;
		pre_path = loc_pre_path(dell, _shgetenv(dell, "PATH="), dell->str_argh[0]);
		if (pre_path)
		{
			dell->pre_path = pre_path;
			sh_cmd_fk(dell);
		}
		else
		{
			if ((sh_active(dell) || _shgetenv(dell, "PATH=")
				|| dell->str_argh[0][0] == '/') && my_sh_cmd(dell, dell->str_argh[0]))
				sh_cmd_fk(dell);
			else if (*(dell->arg_gt) != '\n')
			{
				dell->sh_status = 127;
				sh_echo_err(dell, "not seen\n");
			}
		}
}

/**
 * sh_cmd_fk - forks a new operation using fork and exec to run a cmd
 * @dell: framework and return framework structure
 *
 * Return: void.
 */
void sh_cmd_fk(dell_t *dell)
{
	pid_t lil_pid;

	lil_pid = fork();

	if (lil_pid == -1)
	{
		perror("Error:");
		return;
	}
		if (lil_pid == 0)
		{
			if (execve(dell->pre_path, dell->str_argh, _get_shenviron(dell)) == -1)
			{
				free_dell(dell, 1);
				if (errno == EACCES)
					exit(126);
				exit(1);
			}
		}
		else
		{
			wait(&(dell->sh_status));
			if (WIFEXITED(dell->sh_status))
			{
				dell->sh_status = WEXITSTATUS(dell->sh_status);
				if (dell->sh_status == 126)
					sh_echo_err(dell, "Permission denied\n");
			}
		}
}

