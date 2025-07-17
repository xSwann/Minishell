#include "../includes/exec.h"

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

void	free_cmds(t_cmd *cmd)
{
	int		i;
	t_cmd	*pipe_cmd;

	pipe_cmd = NULL;
	if (!cmd)
		return ;
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			cmd->args[i++] = NULL;
		}
		free(cmd->args);
		cmd->args = NULL;
	}
	while (cmd->infiles && *(cmd->infiles))
	{
		free(*(cmd->infiles));
		*(cmd->infiles)++ = NULL;
	}
	while (cmd->outfiles && *(cmd->outfiles))
	{
		free(*(cmd->outfiles));
		*(cmd->outfiles)++ = NULL;
	}
	pipe_cmd = cmd->pipe_cmd;
	free(cmd);
	return ;
}

int	close_pipe(t_pipex *px)
{
	if (px->pipe_fd[0] && px->pipe_fd[0] >= 0 && close(px->pipe_fd[0]) == -1)
		return (px->pipe_fd[0] = -1, error_printer("close: pipe_fd[0]"), 1);
	px->pipe_fd[0] = -1;
	if (px->pipe_fd[1] && px->pipe_fd[1] >= 0 && close(px->pipe_fd[1]) == -1)
		return (px->pipe_fd[1] = -1, error_printer("close: pipe_fd[1]"), 1);
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
