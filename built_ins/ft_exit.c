
#include "../includes/built_ins.h"
/*
void	exit_without_childs(t_env **env, t_pipex *px)
{
	char	*exit_str;
	int		exit_code;

	exit_code = 0;
	free_cmd(px->cmd);
	close_pipe(px);
	close_fd(&px->infile);
	exit_str = get_env(*env, "EXIT_CODE");
	if (exit_str)
	{
		exit_code = atoi(exit_str);
		free(exit_str);
	}
	free_env(env);
	exit (exit_code);
}*/

void	ft_exit(t_env **env, char **args)
{
    char	*join;
    int		arg_n;
	int		is_negative;

	arg_n = 0;
	is_negative = 0;
    if (!args || !args[0])
    {
        join = get_env(*env, "EXIT_CODE");
		if (!join)
			return (free_env(env), exit(1));
		arg_n = ft_atoi(join);
		return (free(join), join = NULL, free_env(env), exit(arg_n));
    }
	free_env(env);
    if (!args[0][0] || !str_is_num(args[0]))
	{
		fprintf(stderr, "minishell: exit: %s: numeric argument required\n", args[0]);
        return (exit(2));
	}
    if (args[1] && args[1][0])
	{
		fprintf(stderr, "minishell: exit: too many arguments\n");
        return (exit(1));
	}
	if (args[0][0] && args[0][0] == '-')
		is_negative = 1;
    arg_n = ft_atoi(args[0] + is_negative) % 256;
	if (is_negative)
		arg_n = 256 - arg_n;
	free(args[0]);
    return (exit(arg_n));
}
