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
int     ft_pwd(t_env **env);
int     ft_echo(char **str, int param, t_env **env);
int     ft_export(t_env **env, char *arg);
int     is_exportable(char *arg);
int     ft_cd(char *path, t_env **env);
int     ft_unset(t_env **env, char *arg);
int     ft_env(t_env **env);
int ft_exit(t_env **env);

//env_utils
int     init_env(char **envp, t_env **env);
void    free_env(t_env *env, int count);
char *get_env(t_env *env, char *arg);
