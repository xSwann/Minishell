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

char	*path_parser(char *envp, char *cmd)
{
	char	*path;
	int		len;

	path = NULL;
	if (cmd && *cmd && *cmd == '/' && access(cmd, X_OK) == 0)
		return (cmd);
	while (*envp)
	{
		len = 0;
		while (envp[len] && envp[len] != ':')
			len++;
		path = malloc(len + ft_strlen(cmd) + 2);
		if (!path)
			return (error_printer("malloc", "failed"), NULL);
		path_builder(envp, cmd, path, len);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		envp += len;
		if (*envp == ':')
			envp++;
	}
	return (error_printer(cmd, "command not found"), NULL);
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
