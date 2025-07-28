
#include "../../includes/built_ins.h"

int    ft_env(t_env **env)
{
    int i;

    i = 0;
    while ((*env)[i].key)
    {

            printf("%s=", (*env)[i].key);
            printf("%s\n", (*env)[i].value);

        i++;
    }
    return (0);
}
