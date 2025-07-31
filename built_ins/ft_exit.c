#include "../includes/built_ins.h"
#include "../includes/parsing.h"
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

void	exit_printer2(char **args)
{
	write(2, "exit: ", 6);
	error_printer(args[0], "numeric argument required");
	return (exit(2));
}

void	exit_printer1(void)
{
	error_printer("exit", "too many arguments");
	return (exit(1));
}

void	init_arg_n(int *arg_n, char **args, int is_negative)
{
	*arg_n = ft_atoi(args[0] + is_negative) % 256;
	if (is_negative)
		*arg_n = 256 - *arg_n;
}

void	ft_exit(t_env **env, char **args)
{
	char	*join;
	int		arg_n;
	int		is_negative;

	printf("");
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
	if (!args[0][0] || !str_is_num(args[0] + is_negative))
		return (exit_printer2(args));
	if (args[1] && args[1][0])
		return (exit_printer1());
	if (args[0][0] && args[0][0] == '-')
		is_negative = 1;
	init_arg_n(&arg_n, args, is_negative);
	free(args[0]);
	return (exit(arg_n));
}
