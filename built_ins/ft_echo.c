#include "../includes/built_ins.h"

int	is_n(char *str)
{
	int	i;

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

int	handle_cant_echo(char **str, t_env **env, int *i, int *n)
{
	if ((!str || !str[0]) && printf("\n"))
		return (ft_export(env, "EXIT_CODE=0"), 1);
	while (str[++*i] && is_n(str[*i]) == 1)
		*n = 1;
	if (*i >= ft_strslen(str))
		return (ft_export(env, "EXIT_CODE=0"), 1);
	return (0);
}

int	ft_echo(char **str, t_env **env)
{
	int	i;
	int	n;

	i = -1;
	n = 0;
	if (handle_cant_echo(str, env, &i, &n))
		return (1);
	while (str && str[i] && i <= ft_strslen(str) - 2)
	{
		if (str[i])
		{
			if (write(1, str[i], ft_strlen(str[i])) == -1)
				return (1);
			write(1, " ", 1);
		}
		i++;
	}
	if (str[i])
	{
		if (write(1, str[i], ft_strlen(str[i])) == -1)
			return (1);
	}
	if (n == 0)
		printf("\n");
	return (ft_export(env, "EXIT_CODE=0"), 0);
}
