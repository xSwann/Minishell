#ifndef BUILT_INS_H
# define BUILT_INS_H

# include "structs.h"
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "libft.h"

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
int     ft_exit(t_env **env);

//env_utils
int     init_env(char **envp, t_env **env);
void    free_env(t_env *env);
char *get_env(t_env *env, char *arg);

#endif
