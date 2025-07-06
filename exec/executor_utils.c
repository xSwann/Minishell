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
	return (error_printer(cmd), NULL);
}

int	close_pipe(t_pipex *px)
{
	if (px->infile && px->infile >= 0 && close(px->infile) == -1)
		return (px->infile = -1, error_printer("close: infile"), 1);
	if (px->pipe_fd[0] && px->pipe_fd[0] >= 0 && close(px->pipe_fd[0]) == -1)
		return (px->pipe_fd[0] = -1, error_printer("close: pipe_fd[0]"), 1);
	px->pipe_fd[0] = -1;
	if (px->pipe_fd[1] && px->pipe_fd[1] >= 0 && close(px->pipe_fd[1]) == -1)
		return (px->pipe_fd[1] = -1, error_printer("close: pipe_fd[1]"), 1);
	px->pipe_fd[1] = -1;
	return (0);
}

int	wait_execs(pid_t pid)
{
	int	status;

	if (pid < 0)
		return (1);
	if (waitpid(pid, &status, 0) == -1)
		error_printer("waitpid failed");
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}

char	**env_create(t_env *envp)
{
	char	**envp_string_form;
	int		i;

	i = 0;
	envp_string_form = NULL;
	if (!envp || !(*envp->key))
		return (NULL);
	while (envp[i].key)
		i++;
	envp_string_form = malloc(sizeof (char *) * (i + 1));
	if (!envp_string_form)
		return (NULL);
	envp_string_form[i] = NULL;
	while (--i >= 0 && envp[i].key)
		envp_string_form[i] = ft_strjoin(ft_strjoin(envp[i].key, "="), envp[i].value);
	return (envp_string_form);
}
