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

int	path_checker(char *shell_name, t_env **env, char **cmd, char **path)
{
	if (!cmd || !cmd[0] || !cmd[0][0])
		return (CMD_PENDING);
	if (cmd[0][0] == '/' || (cmd[0][0] == '.' && cmd[0][1] == '/'))
	{
		if (access(cmd[0], F_OK) != 0)
			return (CMD_NOT_FOUND);
		return (*path = ft_strdup(cmd[0]), CMD_OK);
	}
	if (!ft_strcmp(cmd[0] + find_last_slash_in_str(cmd[0]), shell_name))
	{
		if (modify_shell_lvl(env, 1))
			return (CMD_NOT_FOUND);
		return (*path = ft_strdup(cmd[0]), CMD_OK);
	}
	return (CMD_PENDING);
}

int	path_parser(char **cmd, char **path, char *path_value)
{
	int		len;
	int		i;

	i = 0;
	if (!cmd || !cmd[0] || !cmd[0][0])
		return (errno = ENOENT, CMD_EMPTY);
	while (path_value && path_value[i])
	{
		len = 0;
		while (path_value[i + len] && path_value[i + len] != ':')
			len++;
		*path = malloc(len + ft_strlen(cmd[0]) + 2);
		if (!*path)
			return (CMD_NO_ACCESS);
		path_builder(path_value + i, cmd[0], *path, len);
		if (access(*path, X_OK) == 0)
			return (CMD_OK);
		free(*path);
		*path = NULL;
		i += len;
		if (path_value[i] == ':')
			i++;
	}
	return (CMD_NOT_FOUND);
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
