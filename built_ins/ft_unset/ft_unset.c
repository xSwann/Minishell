#include "../../includes/built_ins.h"

int	copy_before(t_env *new_env, t_env **env, int *j, int already_in_env)
{
	int	i;

	i = 0;
	while (i < already_in_env)
	{
		new_env[i].key = ft_strdup((*env)[*j].key);
		if (!new_env[i].key)
			return (free_env(&new_env), 1);
		new_env[i].value = ft_strdup((*env)[(*j)++].value);
		if (!new_env[i++].value)
			return (free_env(&new_env), 1);
	}
	return (0);
}

int	find_and_adjust_index(t_env **env, char *arg, int *count)
{
	int	i;
	int	already_in_env;

	i = -1;
	*count = 0;
	while ((*env)[*count].key)
		(*count)++;
	already_in_env = *count;
	while (++i < *count)
	{
		if (!ft_strcmp((*env)[i].key, arg) && (*count)--)
			already_in_env = i;
	}
	return (already_in_env);
}

static int	cpy_remaining_env(t_env *new_env, t_env **env, int start, int count)
{
	int	i;
	int	j;

	i = start;
	j = start + 1;
	while (i < count)
	{
		new_env[i].key = ft_strdup((*env)[j].key);
		if (!new_env[i].key)
			return (free_env(&new_env), 1);
		new_env[i].value = ft_strdup((*env)[j++].value);
		if (!new_env[i++].value)
			return (free_env(&new_env), 1);
	}
	return (0);
}

static int	setup_new_env(t_env **new_env, t_env **env, char *arg, int *in_env)
{
	int	count;
	int	j;

	j = 0;
	*in_env = find_and_adjust_index(env, arg, &count);
	*new_env = init_new_env(count);
	if (!*new_env)
		return (1);
	if (copy_before(*new_env, env, &j, *in_env))
		return (1);
	return (0);
}

int	ft_unset(t_env **env, char *arg)
{
	t_env	*new_env;
	int		already_in_env;
	int		count;

	if (!arg)
		return (ft_export(env, "EXIT_CODE=0"), 0);
	if (setup_new_env(&new_env, env, arg, &already_in_env))
		return (1);
	count = 0;
	find_and_adjust_index(env, arg, &count);
	if (already_in_env != count)
	{
		if (cpy_remaining_env(new_env, env, already_in_env, count))
			return (1);
	}
	free_env(env);
	*env = new_env;
	return (ft_export(env, "EXIT_CODE=0"), 0);
}
