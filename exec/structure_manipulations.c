#include "../includes/exec.h"

int	manage_outfile(t_pipex *px, int fd_stdout)
{
	int	i;

	i = -1;
	if (px->cmd->outfiles && px->cmd->outfiles[0])
	{
		while (px->cmd->outfiles[++i])
		{
			if (px->outfile > 0 && close_fd(&px->outfile))
				return (1);
			px->outfile = open(px->cmd->outfiles[i], \
				px->cmd->open_options, 0644);
			if (px->outfile < 0 && error_printer(NULL, "Permission denied"))
				return (close_fd(&px->infile), close_pipe(px), 1);
		}
	}
	else if (px->cmd->pipe_cmd)
	{
		px->outfile = px->pipe_fd[1];
		px->pipe_fd[1] = -1;
	}
	if (px->outfile && (dup2(px->outfile, fd_stdout) == -1
			|| close_fd(&px->outfile)) && error_printer("dup2", "error"))
		return (close_fd(&px->outfile), close_pipe(px), 1);
	return (close_fd(&px->pipe_fd[1]), 0);
}

int	manage_infile(t_pipex *px, int fd_stdin)
{
	int	i;

	i = -1;
	if (px->cmd->here_doc_fds && px->cmd->here_doc_fds[0] > 0)
		px->infile = px->cmd->here_doc_fds[0];
	else if (px->cmd->infiles && px->cmd->infiles[0])
	{
		while (px->cmd->infiles[++i])
		{
			if (px->infile > 0 && close_fd(&px->infile))
				return (1);
			px->infile = open(px->cmd->infiles[i], O_RDONLY);
			if (px->infile < 0)
				return (error_printer(px->cmd->infiles[i], \
				"No such file or directory"));
		}
	}
	if (px->infile < 0)
		return (error_printer(px->cmd->infiles[i], \
		"No such file or directory"));
	if (px->infile && (dup2(px->infile, fd_stdin) == -1
			|| close_fd(&px->infile)) && error_printer("dup2", "error"))
		return (close_fd(&px->infile), close_pipe(px), 1);
	return (close_fd(&px->pipe_fd[0]), 0);
}

pid_t	*pid_array_builder(t_cmd *cmd)
{
	int		is_built_in;
	pid_t	*pids;
	int		i;

	i = 0;
	is_built_in = 0;
	while (cmd)
	{
		if (cmd->args && cmd->args[0])
			is_built_in = check_built_ins(cmd->args);
		if (!(i == 0 && !cmd->pipe_cmd && cmd->args && cmd->args[0]
				&& (is_built_in > 0 && is_built_in < 7)))
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

int	init_px(char *shell_name, t_cmd **cmd, t_pipex *px)
{
	int	i;

	i = 0;
	px->n_pids = 0;
	px->infile = 0;
	px->cmd = *cmd;
	px->pids = NULL;
	px->outfile = 0;
	if (px->cmd->here_doc_fds && px->cmd->here_doc_fds[0]
		&& px->cmd->here_doc_fds[0] > 0)
	{
		while (px->cmd->here_doc_fds[i + 1] && px->cmd->here_doc_fds[i + 1] > 0)
			close_fd(&px->cmd->here_doc_fds[i++]);
		px->cmd->here_doc_fds[0] = int_switcher(&px->cmd->here_doc_fds[i]);
		if (px->infile && close_fd(&px->infile))
			return (error_printer("pipe", "pipe_fd[0]"), 1);
		px->infile = int_switcher(&px->cmd->here_doc_fds[0]);
		if (px->infile < 0)
			return (error_printer("open", "here_doc_fd"), 1);
	}
	else
		px->here_doc_fd = 0;
	px->shell_name = shell_name;
	px->pids = pid_array_builder(*cmd);
	return (px->first_cmd = *cmd, px->pipe_fd[0] = -1, px->pipe_fd[1] = -1, 0);
}

int	update_px(t_pipex *px)
{
	int	i;

	i = 0;
	px->cmd = free_cmd(px->cmd);
	if (px->outfile && close_fd(&px->outfile))
		return (error_printer("pipe", "pipe_fd[1]"), 1);
	if (px->cmd->here_doc_fds && px->cmd->here_doc_fds[0] && px->cmd->here_doc_fds[0]
		&& px->cmd->here_doc_fds[0] > 0)
	{
		while (px->cmd->here_doc_fds[i + 1] && px->cmd->here_doc_fds[i + 1] > 0)
			close_fd(&px->cmd->here_doc_fds[i++]);
		px->cmd->here_doc_fds[0] = int_switcher(&px->cmd->here_doc_fds[i]);
		if (px->infile && close_fd(&px->infile))
			return (error_printer("pipe", "pipe_fd[0]"), 1);
		px->infile = int_switcher(&px->cmd->here_doc_fds[0]);
		if (px->infile < 0)
			return (error_printer("open", "here_doc_fd"), 1);
	}
	else
		px->here_doc_fd = 0;
	return (0);
}
