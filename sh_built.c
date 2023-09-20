#include "simple_shell.h"

/**
 * _shexit - way out of the shell
 * @dell: structure containing our framework
 * Return: leaves with a given command exit frame
 * (0) if dell.str_argh[0] is != exit
 */
int _shexit(dell_t *dell)
{
	int obsexit;

	if (dell->str_argh[1])
	{
		obsexit = sh_erritoi(dell->str_argh[1]);
		if (obsexit == -1)
		{
			dell->sh_status = 2;
			sh_echo_err(dell, "this number not permitted: ");
			_sheputs(dell->str_argh[1]);
			_sheputchar('\n');
			return (1);
		}
		dell->digit_err = sh_erritoi(dell->str_argh[1]);
		return (-2);
	}
	dell->digit_err = -1;
	return (-2);
}

/**
 * _shcd - alters the present directory of the operation
 * @dell: a structure containing our framework, used to maintain
 * steady function prototype
 * Return: should return ‘0’ always
 */
int _shcd(dell_t *dell)
{
	char *d, *dc, buffer[1024];
	int chdirect;

	d = getcwd(buffer, 1024);
	if (!d)
		_shputs("TODO: >>getswd failed emsg here<<\n");
	if (!dell->str_argh[1])
	{
		dc = _shgetenv(dell, "HOME=");
		if (!dc)
			chdirect =
				chdir((dc = _chgetenv(dell, "PWD=")) ? dc : "/");
		else
			chdirect = chdir(dc);
	}
	else if (_shstrcmp(dell->str_argh[1], "-") == 0)
	{
		if (!_shgetenv(dell, "OLDPWD="))
		{
			_shputs(d);
			_shputchar('\n');
			return (1);
		}
		_shputs(_shgetenv(dell, "OLDPWD=")), _shputchar('\n');
		chdirect = chdir((dir = _shgetenv(dell, "OLDPWD=")) ? dir : "/");
	}
	else
		chdirect = chdir(dell->str_argh[1]);
	if (chdirect == -1)
	{
		sh_echo_err(dell, "cannot cd to ");
		_sheputs(dell->str_argh[1]), _sheputchar('\n');
	}
	else
	{
		_shsetenv(dell, "OLDPWD", _shgetenv(dell, "PWD="));
		_shsetenv(dell, "PWD", getswd(buffer, 1024))
	}
	return (0);
}

/**
 * _shhelp - alterrs present index of the operation
 * @dell: the structure that holds the framework, for maintaining steady
 * function prototype
 * Return: should always return 0
 */
int _shhelp(dell_t *dell)
{
	char **rargh_array;

	rargh_array = dell->str_argh;
	_shputs("pls aid call works. Function not discharged yet \n");
	if (0)
		_shputs(*rargh_array);
	return (0);
}
