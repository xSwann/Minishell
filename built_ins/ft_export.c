
#include <stdlib.h>
#include <string.h>
#include "../includes/built_ins.h"

int     export_loop(t_env **env, char **arg)
{
    int i;
	char *str;

    i = 0;
    while (arg[i])
    {
        ft_export(env, arg[i]);
		str = get_env(*env, "EXIT_CODE");
        if (ft_strcmp(str, "0"))
		{
			if (str)
				free(str);
            return (0);
		}
		if(str)
			free(str);
        i++;
    }
    return (0);
}

int    ft_export(t_env **env, char *arg)
{
    int     arg_already_in_env;
    char    *arg_malloc;
    t_env   *new_env;
    int     count;
    int     i, j;
    char    *has_no_value;

    if (!arg)
        return (ft_env(env), 0);
    if (!is_exportable(arg))
    {
        fprintf(stderr, "export: `%s': not a valid identifier\n", arg);
        return (ft_export(env, "EXIT_CODE=1"));
    }
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
    if (arg_already_in_env == -1)
    {
        new_env = malloc((count + 2) * sizeof *new_env);
        if (!new_env)
            return (free(arg_malloc), 1);
        memset(new_env, 0, (count + 2) * sizeof *new_env);
        j = 0;
        while (j < count)
        {
            new_env[j].key = ft_strdup((*env)[j].key);
            if (!new_env[j].key)
                return (free(arg_malloc), free_env(&new_env), 1);

            new_env[j].value = ft_strdup((*env)[j].value);
            if (!new_env[j].value)
                return (free(arg_malloc), free_env(&new_env), 1);

            j++;
        }
        has_no_value = ft_strchr(arg, '=');
        if (has_no_value)
        {
            new_env[j].value = ft_strdup(has_no_value + 1);
            if (!new_env[j].value)
            {
                free(arg_malloc);
                free_env(&new_env);
                return (1);
            }
        }
        new_env[j].key = arg_malloc;
        arg_malloc = NULL;
        free_env(env);
        *env = new_env;
    }
    else
    {
        free(arg_malloc);
        arg_malloc = NULL;

        has_no_value = ft_strchr(arg, '=');
        if (has_no_value)
        {
            free((*env)[arg_already_in_env].value);
            (*env)[arg_already_in_env].value = ft_strdup(has_no_value + 1);
            if (!(*env)[arg_already_in_env].value)
                return (1);
        }
    }
    return (0);
}

