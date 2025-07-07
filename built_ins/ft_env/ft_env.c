
#include "../../includes/built_ins.h"

int    ft_env(t_env **env)
{
    int i;

    i = 0;
    while ((*env)[i].key)
    {
        if (ft_strcmp((*env)[i].key, "EXIT_CODE") != 0)
        {
            printf("%s=", (*env)[i].key);
            printf("%s\n", (*env)[i].value);
        }
        i++;
    }
    ft_export(env, "EXIT_CODE=0");
    return (0);
}
