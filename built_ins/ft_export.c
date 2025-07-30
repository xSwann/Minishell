#include "../includes/built_ins.h"

int	export_loop(t_env **env, char **arg)
{
	int		i;
	char	*str;

	i = 0;
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

int	ft_export(t_env **env, char *arg)
{
	int		arg_already_in_env;
	char	*arg_malloc;
	char	*has_value;
	t_env	*new_env;
	int		count;
	int		i;

	if (!arg)
		return (ft_env(env), 0);
	if (!is_exportable(arg) && \
		fprintf(stderr, "export: `%s': not a valid identifier\n", arg))
		return (ft_export(env, "EXIT_CODE=1"));
	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	arg_malloc = ft_substr(arg, 0, i);
	if (!arg_malloc)
		return (1);
	count = 0;
	arg_already_in_env = -1;
	while ((*env)[count].key)
	{
		if (!ft_strcmp((*env)[count].key, arg_malloc))
			arg_already_in_env = count;
		count++;
	}
	free(arg_malloc);
	arg_malloc = NULL;
	if (arg_already_in_env == -1)
	{
		new_env = init_new_env(count + 1);
		if (!new_env)
			return (1);
		count = 0;
		while ((*env)[count].key)
		{
			new_env[count].key = ft_strdup((*env)[count].key);
			if (!new_env[count].key)
				return (free_env(&new_env), 1);
			if ((*env)[count].value)
			{
				new_env[count].value = ft_strdup((*env)[count].value);
				if (!new_env[count].value)
					return (free_env(&new_env), 1);
			}
			count++;
		}
		new_env[count].key = ft_substr(arg, 0, i);
		has_value = ft_strchr(arg, '=');
		if (has_value && has_value[1] != '\0')
		{
			new_env[count].value = ft_strdup(has_value + 1);
			if (!new_env[count].value)
				return (free_env(&new_env), 1);
		}
		free_env(env);
		*env = new_env;
	}
	else
	{
		free((*env)[arg_already_in_env].value);
		(*env)[arg_already_in_env].value = NULL;
		has_value = ft_strchr(arg, '=');
		if (has_value + 1)
		{
			(*env)[arg_already_in_env].value = ft_strdup(has_value + 1);
			if (!(*env)[arg_already_in_env].value)
				return (1);
		}
	}
	return (0);
}
