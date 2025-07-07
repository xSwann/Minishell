
#include "../../includes/built_ins.h"

int init_env(char **envp, t_env **env)
{
    int   count;
    int   i;
    int   j;
    int   len;

    count = 0;
    while (envp[count])
        count++;
    *env = malloc(sizeof **env * (count + 2));
    if (!*env)
        exit(EXIT_FAILURE);
    i = 0;
    while (i < count)
    {
        j = 0;
        while (envp[i][j] && envp[i][j] != '=')
            j++;
        (*env)[i].key = ft_substr(envp[i], 0, j);
        len = ft_strlen(envp[i]) - j - 1;
        (*env)[i].value = ft_substr(envp[i], j + 1, len);
        i++;
    }
    (*env)[i].key   = ft_strdup("EXIT_CODE");
    (*env)[i].value = ft_strdup("0");
    count++;
    (*env)[count].key   = NULL;
    (*env)[count].value = NULL;
    return (count);
}
