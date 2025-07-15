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
	//if (px->infile && px->infile >= 0 && close(px->infile) == -1)
	//	return (px->infile = -1, error_printer("close: infile"), 1);
	if (px->pipe_fd[0] && px->pipe_fd[0] >= 0 && close(px->pipe_fd[0]) == -1)
		return (px->pipe_fd[0] = -1, error_printer("close: pipe_fd[0]"), 1);
	px->pipe_fd[0] = -1;
	if (px->pipe_fd[1] && px->pipe_fd[1] >= 0 && close(px->pipe_fd[1]) == -1)
		return (px->pipe_fd[1] = -1, error_printer("close: pipe_fd[1]"), 1);
	px->pipe_fd[1] = -1;
	return (0);
}

int	wait_execs(t_env **envp, t_pipex *px)
{
	int		i;
	int		status;
	char	*status_code;
	char	*exit_code;

	i = -1;
	status = 0;
	while (++i < px->n_pids && px->pids[i])
	{
		if (px->pids[i] <= 0)
			break ;
		if (waitpid(px->pids[i], &status, 0) == -1)
			error_printer("waitpid failed");
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
	}
	free_cmds(px->first_cmd);
	free(px->pids);
	status_code = ft_itoa(status);
	if (status_code)
	{
		exit_code = ft_strjoin("EXIT_CODE=", status_code);
		free(status_code);
		if (exit_code)
			return (ft_export(envp, exit_code), free(exit_code), 0);
	}
	return (status);
}

void	*free_envp(char **envp, int j)
{
	while (j >= 0 && envp && envp[j])
		free(envp[j--]);
	if (j == -2)
	{
		while (envp[++j])
			free(envp[j]);
	}
	return (free (envp), NULL);
}

char	**env_create(t_env *envp)
{
	char	**envp_string_form;
	char	*string_key;
	int		i;
	int		j;

	i = 0;
	if (!envp || !(*envp->key))
		return (NULL);
	while (envp[i].key)
		i++;
	envp_string_form = malloc(sizeof (char *) * (i + 1));
	if (!envp_string_form)
		return (NULL);
	j = -1;
	while (j <= i && envp[j].key)
	{
        //if (ft_strcmp(envp[i].key, "EXIT_CODE") != 0)
		//{
			string_key = ft_strjoin(envp[j].key, "=");
			if (!string_key)
				return (free_envp(envp_string_form, j));
			envp_string_form[j] = ft_strjoin(string_key, envp[j].value);
			if (!envp_string_form[j])
				return (free(string_key), free_envp(envp_string_form, j - 1));
		//}
		j++;
		//fprintf(stderr, "%s\n", envp_string_form[i]);
	}
	return (envp_string_form[j] = NULL, envp_string_form);
}
