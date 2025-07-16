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
	while (*envp)
	{
		len = 0;
		while (envp[len] && envp[len] != ':')
			len++;
		path = malloc(len + ft_strlen(cmd) + 2);
		if (!path)
			return (write(2, "pipex: malloc failed\n", 22), NULL);
		path_builder(envp, cmd, path, len);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		envp += len;
		if (*envp == ':')
			envp++;
	}
	return (error_printer(" command not found"), NULL);
}

int	split_cmd(char **cmd)
{
	char	*cmd_old;
	int		i;
	int		j;

	i = 0;
	j = -1;
	cmd_old = *cmd;
	while (cmd_old && cmd_old[i])
	{
		if (cmd_old[i++] == '/')
			j = i;
	}
	if (j == -1)
		return (0);
	*cmd = ft_strdup(cmd_old + j);
	if (!*cmd)
		return (*cmd = cmd_old, 1);
	return (free(cmd_old), 0);
}
