#include "../includes/built_ins.h"

int    ft_export(t_env **env, char *arg)
{
    int     i;
    int count;
    int j;
    int tmp;
    t_env   *new_env;
    int already_in_env;
    char *arg_malloc;
    char *identifier;

    i = 0;
    count = 0;
    if (!arg)
    {
        ft_env(env);
        return (0);
    }
    while((*env)[count].value)
        count++;
    while (arg[i] && arg[i] != '=')
        i++;
    identifier = ft_substr(arg, 0, i);
    if (!is_exportable(arg))
    {
        fprintf(stderr, "export: `%s': not a valid identifier\n", identifier);
        free(identifier);
        return (ft_export(env, "EXIT_CODE=1"));
    }
    free(identifier);
    i = 0;
    j = 0;
    tmp = 0;
    already_in_env = 0;
    count++;
    new_env = malloc((sizeof(t_env)) * (count + 1));
    while(arg[j] && arg[j] != '=')
        j++;
    if (arg[j] != '=')
    {
        free(new_env);
        count--;
        return (0);
    }
    arg_malloc = ft_substr(arg, 0, j);
    while (i < count - 1)
    {
        if (ft_strcmp((*env)[i].key, arg_malloc) == 0)
            already_in_env = i;
        i++;
    }
    free(arg_malloc);
    i = 0;
    while(i < count - 1)
    {
		if (already_in_env != 0 && i == already_in_env)
        {
            arg_malloc = ft_substr(arg, 0, j);
            new_env[i].key = ft_strdup(arg_malloc);
            free(arg_malloc);
            tmp = j;
            while(arg[j])
                j++;
            arg_malloc = ft_substr(arg, tmp+1, j - tmp);
            new_env[i].value = ft_strdup(arg_malloc);
            free(arg_malloc);
            i++;
        }
		else
		{
			new_env[i].key = ft_strdup((*env)[i].key);
			new_env[i].value = ft_strdup((*env)[i].value);
			i++;
		}
    }
    if (!already_in_env)
    {
        arg_malloc = ft_substr(arg, 0, j);
        new_env[i].key = ft_strdup(arg_malloc);
        free(arg_malloc);
        tmp = j;
        while(arg[j])
            j++;
        new_env[i].value = ft_substr(arg, tmp+1, j - tmp);
    }
    else
        count--;
    new_env[count].key   = NULL;
    new_env[count].value = NULL;
    free_env(*env);
    *env = new_env;
    return(0);
}
