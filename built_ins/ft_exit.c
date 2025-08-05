#include "../includes/built_ins.h"
#include "../includes/parsing.h"
#include "../includes/exec.h"

int	exit_printer2(char **args)
{
	write(2, "exit: ", 6);
	error_printer(args[0], "numeric argument required");
	return (2);
}

void	init_arg_n(int *arg_n, char **args, int is_negative)
{
	*arg_n = ft_atoi(args[0] + is_negative) % 256;
	if (is_negative)
		*arg_n = 256 - *arg_n;
}

void	exit_code_exit(t_env **env, int exit_code)
{
	char	*str;
	char	*str_var;

	str = ft_itoa(exit_code);
	if (str)
	{
		str_var = ft_strjoin("EXIT_CODE=", str);
		free(str);
		str = NULL;
		if (str_var)
		{
			ft_export(env, str_var);
			free(str_var);
			str_var = NULL;
		}
	}
}

int	ft_exit_without_childs(t_env **env, char **args)
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
			return (1);
		arg_n = ft_atoi(join);
		return (free(join), join = NULL, arg_n);
	}
	if (!args[0][0] || !str_is_num(args[0] + is_negative))
		return (exit_printer2(args));
	if (args[1] && args[1][0])
		return (error_printer("exit", "too many arguments"), 1);
	if (args[0][0] && args[0][0] == '-')
		is_negative = 1;
	init_arg_n(&arg_n, args, is_negative);
	return (arg_n);
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
		return (exit(exit_printer2(args)));
	if (args[1] && args[1][0])
		return (error_printer("exit", "too many arguments"), exit(1));
	if (args[0][0] && args[0][0] == '-')
		is_negative = 1;
	init_arg_n(&arg_n, args, is_negative);
	free(args[0]);
	return (exit(arg_n));
}
