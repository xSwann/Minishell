
#include "../../includes/built_ins.h"

void    free_env(t_env *env)
{
    int i;

    i = 0;
    while(env[i].key)
    {
        free(env[i].key);
        free(env[i].value);
        i++;
    }
    free(env);
}
