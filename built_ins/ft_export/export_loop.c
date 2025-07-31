#include "../../includes/built_ins.h"

int	export_loop(t_env **env, char **arg)
{
	int		i;
	char	*str;

	i = 0;
	ft_export(env, "EXIT_CODE=0");
	while (arg[i])
	{
		ft_export(env, arg[i]);
		str = get_env(*env, "EXIT_CODE");
		if (ft_strcmp(str, "0"))
		{
			if (str)
			{
				free(str);
				str = NULL;
			}
			return (0);
		}
		if (str)
		{
			free(str);
			str = NULL;
		}
		i++;
	}
	return (0);
}

int	find_equal_index(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	return (i);
}
