
#include "../../includes/built_ins.h"

t_env    *ft_env(t_env *env, int *nb_of_env_v)
{
    int i;

    i = 0;
    while (i < *nb_of_env_v)
    {
        printf("%s=", env[i].key);
        printf("%s\n", env[i].value);
        i++;
    }
    return (ft_export(env, nb_of_env_v, "EXIT_CODE=0"));
}
