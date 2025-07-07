
#include "built_ins.h"

//le int param sert si l'option -n est requise, dans ce cas la, le param devra etre different de 0
//si l'user entre -n ou -nnn (le nombre qu'il veut) le param doit etre different de 0

int ft_echo(char **str, int param, t_env **env)
{
    int i;
    int len;
    char *exit_code;

    i = 0;
    len = 0;
    if (!str[0])
    {
        if (param == 0)
            printf("\n");
        ft_export(env, "EXIT_CODE=0");
        return (0);
    }
    while(str[i][len])
            len++;
    if (len == 2 && str[i][0] == '$' && str[i][1] == '?' && str[i][2] == '\0')
    {
        exit_code = get_env(*env, "EXIT_CODE");
        printf("%s", exit_code);
        free(exit_code);
    }
    else
        printf("%s", str[i]);
    i++;
    while (str[i])
    {
        len = 0;
        while(str[i][len])
            len++;
        printf("%d", len);
        if (len == 2 && str[i][0] == '$' && str[i][1] == '?' && str[i][3] == '\0')
            printf("%s\n", get_env(*env, "EXIT_CODE"));
        else
            printf(" %s", str[i]);
        i++;
    }
    if (param == 0)
        printf("\n");
    ft_export(env, "EXIT_CODE=0");
    return (0);
}
