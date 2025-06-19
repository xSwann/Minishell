#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "../libft/libft.h"

typedef struct s_env
{
    char *key;
    char *value;
}   t_env;

//FUNCTIONS
int     init_env(char **envp, t_env **env);
void    free_env(t_env *env, int count);
void    ft_env(t_env *env, int nb_of_env_v);
t_env    *ft_export(t_env *env, int *count, char *arg);


//UTILS
