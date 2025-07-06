

#include "../includes/built_ins.h"

t_env *ft_unset(t_env *env, int *count, char *arg)
{
    int i;
    int j;
    t_env   *new_env;
    int already_in_env;

    i = 0;
    j = 0;
    already_in_env = *count;
    while (i < *count)
    {
        if (ft_strcmp(env[i].key, arg) == 0)
        {
            already_in_env = i;
            (*count)--;
        }
        i++;
    }
    new_env = malloc((sizeof(t_env)) * (*count + 1));
    i = 0;
    while (i <= already_in_env)
    {
        new_env[i].key = ft_strdup(env[j].key);
        new_env[i].value = ft_strdup(env[j].value);
        i++;
        j++;
    }
    if(already_in_env != *count)
            j++;
    while (i < *count)
    {
        new_env[i].key = ft_strdup(env[j].key);
        new_env[i].value = ft_strdup(env[j].value);
        i++;
        j++;
    }
    new_env[*count].key   = NULL;
    new_env[*count].value = NULL;
    free_env(env, *count);
    return(ft_export(new_env, count, "EXIT_CODE=0"));
}
