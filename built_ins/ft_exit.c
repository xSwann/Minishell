
#include "../includes/built_ins.h"

int ft_exit(t_env **env)
{
    int i;

    i = 0;
    while ((*env)[i].key)
    {
        if (ft_strcmp((*env)[i].key, "EXIT_CODE") == 0)
            printf ("%s", (*env)[i].value);
        i++;
    }
    return (0);
}