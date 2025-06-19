#include "env.h"

void    ft_env(t_env *env, int nb_of_env_v)
{
    int i;

    i = 0;
    while (i < nb_of_env_v)
    {
        printf("%s=", env[i].key);
        printf("%s\n", env[i].value);
        i++;
    }
}