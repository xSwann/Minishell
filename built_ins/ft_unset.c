

#include "../includes/built_ins.h"

int ft_unset(t_env **env, char *arg)
{
    int i;
    int j;
    t_env   *new_env;
    int already_in_env;
    int count;

    i = 0;
    j = 0;
    count = 0;
    while ((*env)[count].value)
        count++;
    already_in_env = count;
    while (i < count)
    {
        if (ft_strcmp((*env)[i].key, arg) == 0)
        {
            already_in_env = i;
            count--;
        }
        i++;
    }
    new_env = malloc((sizeof(t_env)) * (count + 1));
    i = 0;
    while (i < already_in_env)
    {
        new_env[i].key = ft_strdup((*env)[j].key);
        new_env[i].value = ft_strdup((*env)[j].value);
        i++;
        j++;
    }
    if(already_in_env != count)
            j++;
    while (i < count)
    {
        new_env[i].key = ft_strdup((*env)[j].key);
        new_env[i].value = ft_strdup((*env)[j].value);
        i++;
        j++;
    }
    new_env[count].key   = NULL;
    new_env[count].value = NULL;
    free_env(*env, count);
    *env = new_env;
    ft_export(env, "EXIT_CODE=0");
    return(0);
}
