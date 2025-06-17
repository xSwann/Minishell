#include "exec.h"

int	wait_execs(pid_t *pids, int ac)
{
	int	i;
	int	status;
	int	last_status;

	i = 0;
	last_status = 0;
	while (i < ac - 3)
	{
		if (waitpid(pids[i], &status, 0) == -1)
			error_printer("waitpid failed");
		if (i == ac - 4 && WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		i++;
	}
	return (free(pids), last_status);
}

int	init_px(int ac, char **av, char **envp, t_pipex *px)
{
	if (!px->is_here_doc && ac >= 5)
	{
		px->infile = open(av[1], O_RDONLY);
		if (px->infile < 0)
			return (error_printer(av[1]), 1);
	}
	px->outfile = -1;
	px->prev_fd = px->infile;
	px->pids = malloc(sizeof(int) * ac);
	if (!px->pids)
		return (close(px->infile), error_printer("malloc: pids"), 1);
	px->pids[ac - 3] = 0;
	px->ac = ac;
	px->av = av;
	px->envp = envp;
	px->av_count = 2;
	px->pipe_fd[0] = -1;
	px->pipe_fd[1] = -1;
	return (0);
}

int	child_process(t_pipex *px)
{
	if (px->prev_fd >= 0)
	{
		if ((dup2(px->prev_fd, 0) == -1 && error_printer("dup2: error")
				&& close_pipe(px) < 2) || close_fd(&px->prev_fd) == -1)
			return (free(px->pids), exit(1), 1);
	}
	if (px->av_count < px->ac - 2)
	{
		if ((dup2(px->pipe_fd[1], 1) == -1 && error_printer("dup2: error")
				&& close_pipe(px) < 2) || close_fd(&px->pipe_fd[1]) == -1)
			return (free(px->pids), exit(1), 1);
	}
	if (px->av_count >= px->ac - 2 && manage_outfile(px))
		return (free(px->pids), exit(1), 1);
	exec_cmd(px);
	free(px->pids);
	exit(1);
}

int	pipex(t_pipex *px)
{
	int	pid;

	if (pipe(px->pipe_fd) == -1)
		return (perror("pipe: error"), 1);
	pid = fork();
	if (pid == 0)
	{
		child_process(px);
		return (1);
	}
	else if (pid < 0)
		return (close_pipe(px), error_printer("fork: error"), 1);
	px->pids[px->av_count - 2] = pid;
	if (close_fd(&px->pipe_fd[1]) == -1)
		return (-1);
	if (px->infile == px->prev_fd)
		px->infile = -1;
	if (close_fd(&px->prev_fd) == -1)
		return (1);
	return (px->prev_fd = px->pipe_fd[0], 0);
}

int	command_executor(t_cmd *cmd)
{
	t_pipex	px;

	if (!cmd)
		return (1);
	init_px(px, cmd);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	px;
	int		exit_status;

	exit_status = 0;
	if (ac < 5)
		return (write(2, "format: ./pipex file1 cmd1 ... cmdx file2\n", 42), 1);
	px.is_here_doc = false;
	if (!ft_strncmp("here_doc", av[1], 8) && ac > 5)
	{
		px.infile = ft_here_doc(ac--, av);
		px.is_here_doc = true;
	}
	if (init_px(ac, av, envp, &px))
		return (1);
	while (px.av_count < ac - 1)
	{
		if (pipex(&px))
			return (close_pipe(&px), free(px.pids), 1);
		px.av_count++;
	}
	exit_status = wait_execs(px.pids, px.ac);
	close_pipe(&px);
	return (exit_status);
}
