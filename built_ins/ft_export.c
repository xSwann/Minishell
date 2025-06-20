
#include "built_ins.h"

t_env    *ft_export(t_env *env, int *count, char *arg)
{
    int     i;
    int j;
    int tmp;
    t_env   *new_env;

    i = 0;
    j = 0;
    tmp = 0;
    (*count)++;
    new_env = malloc((sizeof(t_env)) * (*count + 1));

    while(i < *count - 1)
    {
        new_env[i].key = ft_strdup(env[i].key);
        new_env[i].value = ft_strdup(env[i].value);
        i++;
    }
    while(arg[j] && arg[j] != '=')
        j++;
    new_env[i].key = ft_substr(arg, 0, j);
    tmp = j;
    while(arg[j])
        j++;
    new_env[i].value = ft_substr(arg, tmp, j - tmp);
    new_env[*count].key   = NULL;
    new_env[*count].value = NULL;
    free_env(env, *count - 1);
    return(new_env);
}