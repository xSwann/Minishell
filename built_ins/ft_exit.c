
#include "../includes/built_ins.h"

int ft_exit(t_env **env, char *arg)
{
    char *join;
    int arg_n;
    if (!str_is_num(arg))
    {
        fprintf(stderr, "exit: %s: numeric argument required", arg);
        ft_export(env, "EXIT_CODE=2");
        exit(2);
    }
    arg_n = ft_atoi(arg) % 256;
    arg = ft_itoa(arg_n);
    join = ft_strjoin("EXIT_CODE=", arg);
    ft_export(env, join);
    exit(arg_n);
    return (0);
}