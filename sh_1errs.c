#include "simple_shell.h"

/**
 * sh_erritoi - alters a string to an integer
 * @d: string to be altered 
 * Return:  0 if no numbers are seen in string, 
 *      converted number, else return  -1 on error
 */
int sh_erritoi(char *d)
{
	int z = 0;
	unsigned long int reslt = 0;

	if (*d == '+')
		d++;
	for (z = 0;  d[z] != '\0'; z++)
	{
		if (d[z] >= '0' && d[z] <= '9')
		{
			reslt *= 10;
			reslt += (d[z] - '0');
			if (reslt > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (reslt);
}

/**
 * sh_echo_err - outputs an error message
 * @dell: the parameter & return framework struct
 * @str_err: string that contains specifiic error 
 * Return: 0 if no numbers are seen in string, 
 *      converted number, else return  -1 on error
 */
void sh_echo_err(dell_t *dell, char *str_err)
{
	_sheputs(dell->sh_fname);
	_sheputs(": ");
	sh_echo_d(dell->cnt_error, STDERR_FILENO);
	_sheputs(": ");
	_sheputs(dell->str_argh[0]);
        _sheputs(": ");
        _sheputs(str_err);
}

/**
 * sh_echo_d - prints a decimal number (base 10)
 * @ipt: the input integer
 * @dirf: the descriptor file to input to
 *
 * Return: no of characters outputted
 */
int sh_echo_d(int dirf, int ipt)
{
        int (*_shputchar)(char) = _shputchar;
        int z, cnt = 0;
        unsigned int _ast_, cunt;
        if (dirf == STDERR_FILENO)
                _shputchar = _sheputchar;
        if (ipt < 0)
        {
                _ast_ = -ipt;
                _shputchar('-');
                cnt++;
        }
        else
                _ast_ = ipt;
        cunt = _ast_;
        for (z = 1000000000; z > 1; z /= 10)
        {
                if (_ast_ / z)
                {
                        _shputchar('0' + cunt / z);
                        cnt++;
                }
                cunt %= z;
        }
        _shputchar('0' + cunt);
        cnt++;
        return (cnt);
}

/**
 * sh_no_convt - function converter, replica of itoa
 * @no: number to be converted 
 * @bs: convertion base
 * @flg: flags of arguments 
 *
 * Return: involving string
 */
char *sh_no_convt(long int no, int bs, int flg)
{
        static char *ar;
        static char buffer[50];
        char sng = 0;
        char *pt;
        unsigned long num = no;
        if (!(flg & CONVERT_TO_UNSIGNED) && no < 0)
        {
                num = -no;
                sng = '-';
        }
        ar = flg & CONVERT_TO_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
        pt = &buffer[49];
        *pt = '\0';
        do        {
                *--pt = ar[num % bs];
                num /= bs;
        } while (num != 0);
        if (sng)
                *--pt = sng;
        return (pt);
}

/**
 * detach_cmts - function alters initial instance of '#' with '\0'
 * @shbuff: string to alter location
 *
 * Return: should always be 0
 */
void detach_cmts(char *shbuff)
{
        int z;
        for (z = 0; shbuff[z] != '\0'; z++)
                if ((!z || shbuff[z - 1] == ' ') && shbuff[z] == '#')
                { 
                        shbuff[z] = '\0';
                        break;
                }
}
