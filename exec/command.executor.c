#include "exec.h"

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

int	command_executor(t_cmd *cmd)
{
	t_pipex	px;

	if (!cmd)
		return (1);
	init_px(px, cmd);
	return (0);
}
