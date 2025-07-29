
#include "../includes/built_ins.h"

//le int param sert si l'option -n est requise, dans ce cas la, le param devra etre different de 0
//si l'user entre -n ou -nnn (le nombre qu'il veut) le param doit etre different de 0

int is_n(char *str)
{
    int i;

    i = 0;
    if (str[i++] != '-' || ft_strlen(str) <= 1)
        return (0);
    while (str[i])
    {
        if (str[i++] != 'n')
            return (0);
    }
    return (1);
}

int ft_echo(char **str, t_env **env)
{
    int i;
    int n;

    i = -1;
    n = 0;
    if ((!str || !str[0]) && printf("\n"))
		return (ft_export(env, "EXIT_CODE=0"), 0);
    while (str[++i] && is_n(str[i]) == 1)
        n = 1;
    if (i >= ft_strslen(str))
        return (ft_export(env, "EXIT_CODE=0"), 0);
    while (str && str[i] && i <= ft_strslen(str) - 2)
    {
		if (str[i]) 
        	printf("%s ", str[i]);
        i++;
    }
	if (str[i])
		printf("%s", str[i]);
    if (n == 0)
        printf("\n");
    return (ft_export(env, "EXIT_CODE=0"), 0);
}
