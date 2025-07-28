
#include "../../includes/built_ins.h"

void    free_env(t_env **env)
{
    int i;

    i = 0;
	if (!env || !*env)
		return ;
    while(env[i] && (*env)[i].key)
    {
		if ((*env)[i].key)
		{
			free((*env)[i].key);
			(*env)[i].key = NULL;
		}
		if ((*env)[i].value)
		{
			free((*env)[i].value);
			(*env)[i].value = NULL;
		}
        i++;
    }
    free(*env);
	*env = NULL;
}
