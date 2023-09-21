#ifndef _SIMPLE_SHELL_H_
#define _SIMPLE_SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for linking/chain commands */
#define SH_NORM_CMD        0
#define SH_OR_CMD                1
#define SH_AND_CMD                2
#define SH_CHAIN_CMD        3

/* buffers */
#define GET_BUFF_SIZE 1024
#define INPUT_BUF_SIZE 1024
#define FLUSH_BUFF -1

/* using system getline(); ‘1’ */
#define USE_STR_TOK 0
#define USED_GET_LINE 0

/* for convertnumber() */
#define CONVERT_TO_LOWERCASE        1
#define CONVERT_TO_UNSIGNED        2

#define FILE_HISTO     ".simple_shell_sh_history"
#define MAX_HISTO        4096

extern char **environ;

/**
 * struct ltstri - singly link list for the string
 * @no: the amount of area
 * @stri: inputted string
 * @next_nod: upcoming node pointer
 */

typedef struct ltstri
{
	int no;
	char *stri;
	struct ltstri *next_nod;
} lt_t;

/**
 * struct givedell - includes pseudo-explanations to pass dell a function,
 * allow proper prototype for function pointer structure
 * @arg_gt: string gotten from getline with arguments
 * @str_argh: strings of array obtained from arg_gt
 * @pre_path: path of string for the present command
 * @agc: argument count
 * @cnt_error: count error
 * @digit_err: error number for exit()
 * @lines_flagged: count this line of input string if started
 * @sh_fname: filename of the operation
 * @sh_env: local part of environment linked list
 * @environ: usage altered part of environment from ‘LL’ envi
 * @sh_history: history node
 * @sh_alias: alias node
 * @sh_env_changed: if environment was changed, put on
 * @sh_status: executed cmd last return status
 * @cmd_shbuff: pointer to cmd_shbuff location, if chaining
 * @cmd_shbuff_type: COMMAND_type ||, &&, ;
 * @readdirf: the file directory from which to read input
 * @histo_cnt: line amount count of the history
 */

typedef struct givedell
{
	char *arg_gt;
	char **str_argh;
	char *pre_path;
	int agc;
	unsigned int cnt_error;
	int digit_err;
	int lines_flagged;
	char *sh_fname;
	lt_t *sh_env;
	lt_t *sh_history;
	lt_t *sh_alias;
	char **environ;
	int sh_env_changed;
	int sh_status;
	char **cmd_shbuff;
	int cmd_shbuff_type;
	int readdirf;
	int histo_cnt;
} dell_t;
#define DELL_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct _in_built - involves a string inbuilt and function
 * @builtin_typ: command flag of the builtin
 * @builtin_fun: function of the builtin
 */
typedef struct _in_built
{
	char *builtin_typ;
	int (*builtin_fun)(dell_t *);
} inbuilt_tab;


/* sh_stritoi.c */
int sh_active(dell_t *);
int sh_stri_deli(char, char *);
int shalpha(int);
int sh_stritoi(char *);

/* sh_built.c */
int _shexit(dell_t *);
int _shcd(dell_t *);
int _shhelp(dell_t *);

/* sh_1built.c */
int _shhistory(dell_t *);
int _shalias(dell_t *);

/* sh_eviro.c */
int _shenvi(dell_t *);
char *_shgetenv(dell_t *, const char *);
int _setsshenvi(dell_t *);
int _shunsetsenv(dell_t *);
int occupy_env_lt(dell_t *);

/* sh_errs.c */
void _sheputs(char *);
int _sheputchar(char);
int _shputdirf(char ca, int dirf);
int _shputsdirf(char *stri, int dirf);

/* sh_1errs.c */
int sh_erritoi(char *);
void sh_echo_err(dell_t *, char *);
int sh_echo_d(int, int);
char *sh_no_convt(long int, int, int);
void detach_cmts(char *);

/* sh_ext.c */
char *_shstrncpy(char *, char *, int);
char *_shstrncat(char *, char *, int);
char *_shstrchr(char *, char);

/* sh_gtln.c */
ssize_t sh_ret_input(dell_t *);
int _shgetline(dell_t *, char **, size_t *);
void sh_sginHandlers(int);

/* sh_gtenvi.c */
char **_get_shenviron(dell_t *);
int _unset_shenv(dell_t *, char *);
int _shsetenv(dell_t *, char *, char *);

/* sh_getdell.c */
void sh_free_dell(dell_t *);
void sh_set_dell(dell_t *, char **);
void free_dell(dell_t *, int);

/* sh_hist.c */
char *sh_get_hist(dell_t *);
int sh_wri_histo(dell_t *);
int sh_rd_histo(dell_t *);
int sh_histo_list_bld(dell_t *, char *, int linecnt);
int sh_reno_histo(dell_t *dell);

/* sh_lts.c */
lt_t *nod_put(lt_t **, const char *, int);
lt_t *sh_nod_put_end(lt_t **, const char *, int);
size_t prti_ltstri(const lt_t *);
int sh_del_node_at_idx(lt_t **, unsigned int);
void sh_frlt(lt_t **);

/* sh_1lts.c */
size_t lt_lent(const lt_t *);
char **sh_lt_to_strn(lt_t *);
size_t prti_lt(const lt_t *);
lt_t *sh_nod_strt_with(lt_t *, char *, char);
ssize_t shget_ndx_nod(lt_t *, lt_t *);

/* sh_mry.c */
int shbfree(void **);

/* sh_prser.c*/
int my_sh_cmd(dell_t *, char *);
char *replica(char *, int, int);
char *loc_pre_path(dell_t *, char *, char *);

/* sh_allore.c */
char *_shmemset(char *, char, unsigned int);
void shfree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* sh_loopp.c */
int ssh(dell_t *, char **);
int loc_inbuilt(dell_t *);
void fd_loc_cmd(dell_t *);
void sh_cmd_fk(dell_t *);

/* sh_stri.c */
int _strlen(char *);
int _shstrcmp(char *, char *);
char *strt_with(const char *, const char *);
char *_strcat(char *, char *);

/* sh_1stri.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _shputs(char *);
int _shputchar(char);

/* sh_tokniz.c */
char **shstritow(char *, char *);
char **shstritow2(char *, char);

/* sh_svar.c */
int sh_is_chn(dell_t *, char *, size_t *);
void sh_obs_chn(dell_t *, char *, size_t *, size_t, size_t);
int ret_sh_alias(dell_t *);
int ret_varis(dell_t *);
int sh_rep_stri(char **, char *);

/* looppssh.c */
int looppssh(char **);

#endif

