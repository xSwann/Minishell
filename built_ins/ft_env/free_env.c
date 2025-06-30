
#include "../built_ins.h"

void    free_env(t_env *env, int count)
{
    int i;

    i = 0;
    while(i <= count)
    {
        free(env[i].key);
        free(env[i].value);
        i++;
    }
    free(env);
}
