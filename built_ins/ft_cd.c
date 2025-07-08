
#include "../includes/built_ins.h"

int ft_cd(char *path, t_env **env)
{
    char *path_env;
    char cwd[4097];
    int i;

    i = 0;
    if (!path)
    {
        path = get_env(*env, "HOME");
        if (!path)
        {
            printf("cd: PWD not set\n");
            ft_export(env, "EXIT_CODE=1");
            return (0);
        }
    }
    else if (ft_strcmp(path, "-") == 0)
    {
        path = get_env(*env, "OLDPWD");
        if (!path)
        {
            printf("minishell: cd: OLDPWD not set\n");
            ft_export(env, "EXIT_CODE=1");
            return (0);
        }
    }
    else
        path = ft_strdup(path);
    if (chdir(path) != 0)
    {
        fprintf(stderr, "cd: %s: No such file or directory\n", path);
        free(path);
        return (ft_export(env, "EXIT_CODE=1"));
    }
    while((*env)[i].key && ft_strcmp((*env)[i].key, "PWD") != 0)
        i++;
    path_env = ft_strjoin("OLDPWD=", (*env)[i].value);
    ft_export(env, path_env);
    free(path_env);
    getcwd(cwd, sizeof(cwd));
    path_env = ft_strjoin("PWD=", cwd);
    ft_export(env, path_env);
    free(path_env);
    free(path);
    ft_export(env, "EXIT_CODE=0");
    return (0);
}
