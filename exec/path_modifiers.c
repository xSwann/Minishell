#include "../includes/exec.h"

void	path_builder(char *envp, char *cmd, char *path, int len)
{
	int	i;

	i = 0;
	while (envp && envp[i] && i < len)
	{
		path[i] = envp[i];
		i++;
	}
	path[i] = '/';
	i++;
	while (cmd && *cmd)
	{
		path[i] = *cmd++;
		i++;
	}
	path[i] = '\0';
}

int	modify_shell_lvl(t_env **env, int modifier)
{
	int		shell_lvl_int;
	char	*shell_lvl_str;
	char	*shell_lvl_str2;

	shell_lvl_str = get_env(*env, "SHLVL");
	if (shell_lvl_str)
	{
		shell_lvl_int = ft_atoi(shell_lvl_str) + modifier;
		free(shell_lvl_str);
		shell_lvl_str = ft_itoa(shell_lvl_int);
		if (shell_lvl_str)
		{
			shell_lvl_str2 = ft_strjoin("SHLVL=", shell_lvl_str);
			free(shell_lvl_str);
			if (shell_lvl_str2 && ft_export(env, shell_lvl_str2))
				return (free(shell_lvl_str2), 1);
			return (0);
		}
		return (1);
	}
	return (1);
}

int	check_path_value(char *shell_name, t_env **env, char *cmd)
{
	int		i;

	if (access(cmd, X_OK) != 0)
		return (0);
	i = find_last_slash_in_str(cmd);
	if (!ft_strcmp(cmd + i, shell_name))
	{
		if (modify_shell_lvl(env, 1))
			return (0);
		return (1);
	}
	if (cmd[0] == '/')
		return (1);
	return (0);
}

char	*path_parser(char *shell_name, t_env **env, char *cmd)
{
	char	*path_value;
	char	*path;
	int		len;
	int		i;

	i = 0;
	path = NULL;
	if (cmd && *cmd && check_path_value(shell_name, env, cmd))
		return (cmd);
	path_value = get_env(*env, "PATH");
	if (!path_value)
		return (error_printer(cmd, "PATH not found"), NULL);
	while (cmd && path_value[i])
	{
		len = 0;
		while (path_value[i + len] && path_value[i + len] != ':')
			len++;
		path = malloc(len + ft_strlen(cmd) + 2);
		if (!path)
			return (free(path_value), error_printer("malloc", "failed"), NULL);
		path_builder(path_value + i, cmd, path, len);
		if (access(path, X_OK) == 0)
			return (free(path_value), path);
		free(path);
		i += len;
		if (path_value[i] == ':')
			i++;
	}
	return (free(path_value), error_printer(cmd, "command not found"), NULL);
}

int	find_last_slash_in_str(char *cmd)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (cmd && cmd[i])
	{
		if (cmd[i++] == '/')
			j = i;
	}
	return (j);
}
