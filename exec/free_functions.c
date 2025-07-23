#include "../includes/exec.h"

char	**free_array(char **array)
{
	int	i;

	if (!array || !array[0])
		return (NULL);
	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i++] = NULL;
	}
	free(array);
	return (NULL);
}

t_cmd	*free_cmd(t_cmd *cmd)
{
	t_cmd	*prev_cmd;

	prev_cmd = NULL;
	if (!cmd)
		return (NULL);
	cmd->args = free_array(cmd->args);
	cmd->infiles = free_array(cmd->infiles);
	cmd->outfiles = free_array(cmd->outfiles);
	prev_cmd = cmd;
	cmd = cmd->pipe_cmd;
	free(prev_cmd);
	prev_cmd = NULL;
	return (cmd);
}

int	close_pipe(t_pipex *px)
{
	if (px->pipe_fd[0] && px->pipe_fd[0] >= 0 && close(px->pipe_fd[0]) == -1)
		return (px->pipe_fd[0] = -1, error_printer("close", "pipe_fd[0]"), 1);
	px->pipe_fd[0] = -1;
	if (px->pipe_fd[1] && px->pipe_fd[1] >= 0 && close(px->pipe_fd[1]) == -1)
		return (px->pipe_fd[1] = -1, error_printer("close", "pipe_fd[1]"), 1);
	px->pipe_fd[1] = -1;
	return (0);
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
