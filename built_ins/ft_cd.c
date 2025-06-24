
#include "built_ins.h"

t_env    *ft_cd(char *path, t_env *env, int *count)
{

    t_env *new_env;
    char *word;
    char *path_env;
    char cwd[4097];
    int i;

    i = 0;
    new_env = NULL;
    if (chdir(path) != 0)
    {
        printf("this path doesn't exist");
        return (env);
    }
    getcwd(cwd, sizeof(cwd));
    while(i < *count && ft_strcmp(env[i].key, "PWD") != 0)
        i++;
    path_env = ft_strjoin("OLDPWD=", env[i].value);
    new_env = ft_export(env, count, path_env);
    free(path_env);
    if (ft_strcmp(path, "/") == 0)
    {
        word = get_env(new_env, count, "HOME");
        path_env = ft_strjoin("PWD=", word);
        free(word);
    }
    else
    { 
        getcwd(cwd, sizeof(cwd));
        path_env = ft_strjoin("PWD=", cwd);
    }
    new_env = ft_export(new_env, count, path_env);
    free(path_env);
    return (new_env);
}