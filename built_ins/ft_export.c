#include "../includes/built_ins.h"

int     export_loop(t_env **env, char **arg)
{
    int i;

    i = 0;
    while (arg[i])
    {
        ft_export(env, arg[i]);
        if (ft_strcmp(get_env(*env, "EXIT_CODE"), "0"))
            return (0);
        i++;
    }
    return (0);
}


int    ft_export(t_env **env, char *arg)
{
    int		arg_already_in_env;
    char	*arg_malloc;
    t_env   *new_env;
    int		count;
    int		i;
    int		j;

    if (!arg)
        return (ft_env(env), 0);
    if (!is_exportable(arg))
    {
        fprintf(stderr, "export: `%s': not a valid identifier\n", arg);
        return (ft_export(env, "EXIT_CODE=1"));
    }
    i = 0;
    count = -1;
    arg_already_in_env = -1;
    while (arg[i] && arg[i] != '=')
		i++;
	arg_malloc = ft_substr(arg, 0, i);
	if (!arg_malloc)
		return (1);
    while ((*env)[++count].key)
	{
		if (!ft_strcmp((*env)[count].key, arg_malloc))
			arg_already_in_env = count;
	}
	if (arg_already_in_env == -1)
	{
		new_env = malloc((sizeof(t_env)) * (count + 2));
		if (!new_env)
			return (free(arg_malloc), 1);
		j = -1;
		while (++j < count)
		{
			new_env[j].key = ft_strdup((*env)[j].key);
			if (!new_env[j].key)
				return (free(arg_malloc), free_env(&new_env), 1);
			new_env[j].value = ft_strdup((*env)[j].value);
			if (!new_env[j].value)
				return (free(arg_malloc), free_env(&new_env), 1);
		}
		new_env[j].key = arg_malloc;
		arg_malloc = NULL;
		new_env[j].value = ft_strdup(arg + i + 1);
		if (!new_env[j++].value)
			return (free_env(&new_env), 1);
		new_env[j].key = NULL;
		new_env[j].value = NULL;
		free_env(env);
		*env = new_env;
	}
	else
	{
		free(arg_malloc);
		arg_malloc = NULL;
		if ((*env)[arg_already_in_env].value)
		{
			free((*env)[arg_already_in_env].value);
			(*env)[arg_already_in_env].value = NULL;
		}
		if (arg[i + 1])
		{
			(*env)[arg_already_in_env].value = ft_strdup(arg + i + 1);
			if (!(*env)[arg_already_in_env].value)
				return (1);
		}
	}
    return(0);
}
