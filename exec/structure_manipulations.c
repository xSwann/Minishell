
#include "../includes/exec.h"
#include <unistd.h>

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
	if (cmd->infile)
	{
		free(cmd->infile);
		cmd->infile = NULL;
	}
	if (cmd->outfile)
	{
		free(cmd->outfile);
		cmd->outfile = NULL;
	}
	pipe_cmd = cmd->pipe_cmd;
	free(cmd);
	return ;
}

int	manage_outfile(t_pipex *px, int fd_stdout)
{
	if (px->cmd->outfile && px->cmd->open_options)
	{
		if (px->cmd->open_options == (O_WRONLY | O_CREAT | O_TRUNC))
			px->outfile = open(px->cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (px->cmd->open_options == (O_WRONLY | O_CREAT | O_APPEND))
			px->outfile = open(px->cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else if (px->cmd->pipe_cmd)
		px->outfile = px->pipe_fd[1];
	if (px->outfile < 0 && error_printer(px->cmd->outfile))
		return (close_fd(&px->infile), close_pipe(px), 1);
	if (px->outfile && dup2(px->outfile, fd_stdout) == -1 
		&& error_printer("dup2: error"))
		return (close_fd(&px->outfile), close_pipe(px), 1);
	return (0);
}

int	manage_infile(t_pipex *px, int fd_stdin)
{
	if (px->cmd->here_doc_fd)
		px->infile = px->cmd->here_doc_fd;
	else if (px->cmd->infile)
		px->infile = open(px->cmd->infile, O_RDONLY);
	if (px->infile < 0)
		return (write(2, " No such file or directory\n", 26), 1);
	if (px->infile && dup2(px->infile, fd_stdin) == -1 
		&& error_printer("dup2: error"))
		return (close_fd(&px->infile), close_pipe(px), 1);
	return (0);
}

pid_t	*pid_array_builder(t_cmd *cmd)
{
	pid_t	*pids;
	int		i;

	i = 0;
	while (cmd)
	{
		if (cmd->args && cmd->args[0]
		&& (!(!ft_strcmp("cd", cmd->args[0]) || !ft_strcmp("env", cmd->args[0])
		|| !ft_strcmp("echo", cmd->args[0]) || !ft_strcmp("export", cmd->args[0])
		|| !ft_strcmp("pwd", cmd->args[0]) || !ft_strcmp("unset", cmd->args[0])
		|| !ft_strcmp("exit", cmd->args[0]))))
			i++;
		cmd = cmd->pipe_cmd;
	}
	if (!i)
		return (NULL);
	pids = (pid_t *)ft_calloc(i + 1, sizeof(pid_t));
	if (!pids)
		return (NULL);
	return (pids);
}

int	init_px(t_cmd **cmd, t_pipex *px)
{
	if (!cmd || !(*cmd) || !(*cmd)->args)
		return (fprintf(stderr, "\n\ninit_px : cmd is NULL\n\n"));
	px->n_pids = 0;
	px->infile = 0;
	px->cmd = *cmd;
	px->pids = NULL;
	px->outfile = 0;
	px->here_doc_fd = 0;
	px->pipe_fd[0] = -1;
	px->pipe_fd[1] = -1;
	px->first_cmd = *cmd;
	px->args = (*cmd)->args;
	px->pids = pid_array_builder(*cmd);
	//px->stdin_backup = dup(STDIN_FILENO);
	//px->stdout_backup = dup(STDOUT_FILENO);
	//fprintf(stderr, "		px->here_doc_fd = %i || px->pipe_fd[0] = %i || px->pipe_fd[1] = %i\n\
	//	px->outfile = %i || px->infile = %i || px->infile = %i\n\
	//	args[0] = %s || t_cmd = %p || pid = %i\n", px->here_doc_fd, \
	//	px->pipe_fd[0], px->pipe_fd[1], px->outfile, px->infile, \
	//	px->infile, px->args[0], px->cmd, px->pids[0]);
	return (0);
}

int	update_px(t_pipex *px)
{
	if (!px->cmd->pipe_cmd)
		return (px->cmd = NULL, 0);
	px->args = px->cmd->pipe_cmd->args;
	px->outfile = 0;
	if (px->cmd->pipe_cmd->here_doc_fd)
	{
		if (px->infile && close_fd(&px->infile))
			return (error_printer("pipe_fd[0]"), 1);
		px->infile = px->cmd->pipe_cmd->here_doc_fd;
		if (px->infile < 0)
			return (error_printer("here_doc_fd"), 1);
	}
	else
		px->here_doc_fd = 0;
	px->cmd = px->cmd->pipe_cmd;
	return (0);
}
