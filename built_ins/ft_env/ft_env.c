
#include "../../includes/built_ins.h"

int    ft_env(t_env **env)
{
    int i;

    i = 0;
    while ((*env)[i].key)
    {
		if ((*env)[i].key)
            printf("%s=", (*env)[i].key);
		if ((*env)[i].value)
            printf("%s", (*env)[i].value);
        printf("\n");
        i++;
    }
    return (0);
}
