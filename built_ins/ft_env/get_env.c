#include "../../includes/built_ins.h"

char *get_env(t_env *env, int *count, char *arg)
{
    int i;

    i = 0;
    while (i < *count)
    {
        if (ft_strcmp(env[i].key, arg) == 0)
            return(ft_strdup(env[i].value));
        i++;
    }
    return (NULL);
}
