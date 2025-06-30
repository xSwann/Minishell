#include "exec.h"

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

int	free_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return (1);
	while (args[i])
		free(args[i++]);
	return (free(args), 1);
}

int	manage_outfile(t_pipex *px)
{
	if (px->outfile < 0)
		return (px->outfile = -1, close_pipe(px), 1);
	if (dup2(px->outfile, 1) == -1 && error_printer("dup2: error"))
		return (close_fd(&px->outfile), close_pipe(px), 1);
	if (close_fd(&px->outfile) == -1)
		return (close_pipe(px), 1);
	return (0);
}

int	close_pipe(t_pipex *px)
{
	//fprintf(stderr, "En fin de pipe on a :\n\
	//	px->infile = %i || px->outfile = %i || px->pipe_fd[0] = %i || px->pipe_fd[1] = %i\n", \
	//	px->infile, px->outfile, px->pipe_fd[0], px->pipe_fd[1]);
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
