#include "../../includes/built_ins.h"

int	ft_env(t_env **env, char **arg)
{
	int	i;

	i = 0;
	if (arg && arg[0])
		return (1);
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
