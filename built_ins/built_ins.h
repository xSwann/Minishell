#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../libft/libft.h"

//ENV STRUCT
typedef struct s_env
{
    char *key;
    char *value;
}   t_env;

//FUNCTIONS
t_env    *ft_pwd(t_env *env, int *count);
t_env    *ft_echo(char **str, int param, t_env *env, int *count);
t_env   *ft_export(t_env *env, int *count, char *arg);
int     is_exportable(char *arg);
t_env   *ft_cd(char *path, t_env *env, int *count);
t_env   *ft_unset(t_env *env, int *count, char *arg);
t_env    *ft_env(t_env *env, int *nb_of_env_v);

//env_utils
int     init_env(char **envp, t_env **env);
void    free_env(t_env *env, int count);
char    *get_env(t_env *env, int *count, char *arg);
