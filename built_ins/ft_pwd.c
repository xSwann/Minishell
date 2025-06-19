
#include "built_ins.h"
#include <string.h>
void    ft_pwd(t_env *env, int count)
{
    int i;

    i = 0;
    while(i < count && strcmp(env[i].key, "PWD") != 0)
        i++;
    printf("%s", env[i].value);
}