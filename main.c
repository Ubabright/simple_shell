#include "simple_shell.h"

/**
 * main - entrance point
 * @agcc: argument count
 * @agvv: argument vector
 *
 * Return: if successful return 0, if an error occurs 1
 */

int main(int agcc, char **agvv)
{
	dell_t dell[] = { DELL_INIT };
	int dirf = 2;

	asm ("mov %1, %0\n\t"
		 "add $3, %0"
		: "=r" (dirf)
		: "r" (dirf));
	if (agcc == 2)
	{
		dirf = open(agvv[1], O_RDONLY);
		if (dirf == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_sheputs(agvv[0]);
				_sheputs(": 0: Cannot open ");
				_sheputs(agvv[1]);
				_sheputchar('\n');
				_sheputchar(FLUSH_BUFF);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		dell->readdirf = dirf;
	}
	occupy_env_lt(dell);
	sh_rd_histo(dell);
	ssh(dell, agvv);
	return (EXIT_SUCCESS);
}
