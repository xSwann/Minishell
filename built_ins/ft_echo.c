
#include "../includes/built_ins.h"

//le int param sert si l'option -n est requise, dans ce cas la, le param devra etre different de 0
//si l'user entre -n ou -nnn (le nombre qu'il veut) le param doit etre different de 0

int is_n(char *str)
{

    int i;

    i = 0;

    if (str[i] != '-' || ft_strlen(str) <= 1)
        return (0);
    i++;
    while (str[i])
    {
        if (str[i] != 'n')
            return (0);
        i++;
    }
    return (1);
}

int ft_echo(char **str, t_env **env)
{
    int i;
    int n;

    i = 0;
    n = 0;
    if (!str || !str[0])
    {
        ft_export(env, "EXIT_CODE=0");
        printf("\n");
        return (0);
    }
    while (str[i] && is_n(str[i]) == 1)
    {
        n = 1;
        i++;
    }
    if (i >= ft_strslen(str))
    {
        ft_export(env, "EXIT_CODE=0");
        return (0);
    }
    while (str && str[i] && i <= ft_strslen(str) - 2)
    {
		if (str[i][0]) 
        	printf("%s ", str[i]);
        i++;
    }
	printf("%s", str[i]);
    if (n == 0)
        printf("\n");	
    ft_export(env, "EXIT_CODE=0");
    return (0);
}
