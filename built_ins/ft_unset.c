

#include "../includes/built_ins.h"

int     unset_loop(t_env **env, char **arg)
{
    int i;

    i = 0;
    while (arg[i])
    {
        if (ft_unset(env, arg[i]))
            return (ft_export(env, "EXIT_CODE=1"), 1);
        i++;
    }
    return (0);
}

t_env	*init_new_env(int count)
{
	t_env	*new_env;
	int		i;

	new_env = malloc((sizeof(t_env)) * (count + 1));
	if (!new_env)
		return (NULL);
	i = -1;
	while (++i <= count)
	{
		new_env[i].key = NULL;
		new_env[i].value = NULL;
	}
	return (new_env);
}

int ft_unset(t_env **env, char *arg)
{
    int i;
    int j;
    t_env   *new_env;
    int already_in_env;
    int count;

    i = -1;
    j = 0;
    count = 0;
    if (!arg)
    {
        if (ft_export(env, "EXIT_CODE=0"))
			return (1);
        return (0);
    }
    while ((*env)[count].key)
        count++;
    already_in_env = count;
    while (++i < count)
    {
        if (!ft_strcmp((*env)[i].key, arg) && count--)
            already_in_env = i;
    }
    new_env = init_new_env(count);
	if (!new_env)
		return (1);
    i = 0;
    while (i < already_in_env)
    {
        new_env[i].key = ft_strdup((*env)[j].key);
		if (!new_env[i].key)
			return (free_env(&new_env), 1);
        new_env[i].value = ft_strdup((*env)[j++].value);
		if (!new_env[i++].value)
			return (free_env(&new_env), 1);
    }
    if (already_in_env != count)
            j++;
    while (i < count)
    {
        new_env[i].key = ft_strdup((*env)[j].key);
		if (!new_env[i].key)
			return (free_env(&new_env), 1);
        new_env[i].value = ft_strdup((*env)[j++].value);
		if (!new_env[i++].value)
			return (free_env(&new_env), 1);
    }
    free_env(env);
    return (*env = new_env, ft_export(env, "EXIT_CODE=0"), 0);
}
