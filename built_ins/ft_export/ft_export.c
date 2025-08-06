#include "../../includes/built_ins.h"

int	is_arg_already_in_env(char *arg, int *alrdy_in_env, t_env **env, int *count)
{
	char	*arg_malloc;
	int		i;

	i = 0;
	i = find_equal_index(arg);
	arg_malloc = ft_substr(arg, 0, i);
	if (!arg_malloc)
		return (1);
	*count = 0;
	*alrdy_in_env = -1;
	while ((*env)[*count].key)
	{
		if (!ft_strcmp((*env)[*count].key, arg_malloc))
			*alrdy_in_env = *count;
		(*count)++;
	}
	free(arg_malloc);
	arg_malloc = NULL;
	return (0);
}

int	copy_old_env(t_env *new_env, t_env **env, int *count)
{
	if (!new_env)
		return (1);
	(*count) = 0;
	while ((*env)[*count].key)
	{
		new_env[*count].key = ft_strdup((*env)[*count].key);
		if (!new_env[*count].key)
			return (free_env(&new_env), 1);
		if ((*env)[*count].value)
		{
			new_env[*count].value = ft_strdup((*env)[*count].value);
			if (!new_env[*count].value)
				return (free_env(&new_env), 1);
		}
		(*count)++;
	}
	return (0);
}

int	search_and_replace_old_value(t_env **env, int arg_already_in_env, char *arg)
{
	char	*has_value;

	free((*env)[arg_already_in_env].value);
	(*env)[arg_already_in_env].value = NULL;
	has_value = ft_strchr(arg, '=');
	if (has_value + 1)
	{
		(*env)[arg_already_in_env].value = ft_strdup(has_value + 1);
		if (!(*env)[arg_already_in_env].value)
			return (1);
	}
	return (0);
}

int	add_arg_to_new_env(int count, t_env **env, char *arg)
{
	int		i;
	char	*has_value;
	t_env	*new_env;

	i = 0;
	new_env = init_new_env(count + 1);
	if (copy_old_env(new_env, env, &count))
		return (1);
	i = find_equal_index(arg);
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
	return (0);
}

int	ft_export(t_env **env, char *arg)
{
	int		arg_already_in_env;
	int		count;
	int		i;

	if (!arg)
		return (ft_env(env, NULL), 0);
	if (!is_exportable(arg))
	{
		write(2, "export: `", 9);
		write(2, arg, ft_strlen(arg));
		write(2, "': not a valid identifier\n", 26);
		return (ft_export(env, "EXIT_CODE=1"));
	}
	i = 0;
	arg_already_in_env = 0;
	if (is_arg_already_in_env(arg, &arg_already_in_env, env, &count))
		return (1);
	if (arg_already_in_env == -1)
		return (add_arg_to_new_env(count, env, arg));
	else
		return (search_and_replace_old_value(env, arg_already_in_env, arg));
	return (0);
}
