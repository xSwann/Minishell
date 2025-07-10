
#include "../includes/built_ins.h"

int ft_exit(t_env **env, char **arg)
{
    char *join;
    int arg_n;
    if (!arg || !arg[1])
    {
        arg_n = ft_atoi(get_env(*env, "EXIT_CODE"));
        exit(arg_n);
        return (0);
    }   
    if (ft_strslen(arg) > 2)
    {
        fprintf(stderr, "exit: too many arguments");
        ft_export(env, "EXIT_CODE=1");
        return (0);
    }
    if (!str_is_num(arg[1]))
    {
        fprintf(stderr, "exit: %s: numeric argument required", arg[1]);
        ft_export(env, "EXIT_CODE=2");
        exit(2);
    }
    arg_n = ft_atoi(arg[1]) % 256;
    arg[1] = ft_itoa(arg_n);
    join = ft_strjoin("EXIT_CODE=", arg[1]);
    ft_export(env, join);
    exit(arg_n);
    return (0);
}
