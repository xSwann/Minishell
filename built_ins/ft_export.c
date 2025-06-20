
//permet de mettre des mouvelles variables dans le env, si la cle de la variable existe deja, remplace juste sa value
//peut aussi etre utiliser pour mettre a jour des values, (exemple: pwd)
#include "built_ins.h"

t_env    *ft_export(t_env *env, int *count, char *arg)
{
    int     i;
    int j;
    int tmp;
    t_env   *new_env;
    int already_in_env;
    char *arg_malloc;

    i = 0;
    j = 0;
    tmp = 0;
    already_in_env = 0;
    (*count)++;
    new_env = malloc((sizeof(t_env)) * (*count + 1));
    while(arg[j] && arg[j] != '=')
        j++;
    arg_malloc = ft_substr(arg, 0, j);
    while (i < *count - 1)
    {
        if (ft_strcmp(env[i].key, arg_malloc) == 0)
            already_in_env = i;
        i++;
    }
    free(arg_malloc);
    i = 0;
    while(i < *count - 1)
    {
        if (already_in_env != 0 && i == already_in_env)
        {
            arg_malloc = ft_substr(arg, 0, j);
            new_env[i].key = ft_strdup(arg_malloc);
            free(arg_malloc);
            tmp = j;
            while(arg[j])
                j++;
            arg_malloc = ft_substr(arg, tmp+1, j - tmp);
            new_env[i].value = ft_strdup(arg_malloc);
            free(arg_malloc);
            i++;
        }
        new_env[i].key = ft_strdup(env[i].key);
        new_env[i].value = ft_strdup(env[i].value);
        i++;
    }
    if (!already_in_env)
    {
        arg_malloc = ft_substr(arg, 0, j);
        new_env[i].key = ft_strdup(arg_malloc);
        free(arg_malloc);
        tmp = j;
        while(arg[j])
            j++;
        new_env[i].value = ft_substr(arg, tmp+1, j - tmp);
    }
    else
        (*count)--;
    new_env[*count].key   = NULL;
    new_env[*count].value = NULL;
    free_env(env, *count - 1);
    return(new_env);
}