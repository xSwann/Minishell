#include "../../includes/built_ins.h"

char *get_env(t_env *env, char *arg)
{
    int i;

    i = 0;
    while (env[i].value)
    {
        if (ft_strcmp(env[i].key, arg) == 0)
            return(ft_strdup(env[i].value));
        i++;
    }
    return (NULL);
}
