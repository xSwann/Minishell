#include "../includes/exec.h"
#include <unistd.h>

void	executor(char **envp, t_pipex *px)
{
	char	*path;
	int		i;

	if ((!px->args || !px->args[0]) && write(2, "Pipex : Empty command\n", 22)
		&& free_args(px->args))
	{
		close_fd(&px->pipe_fd[1]);
		exit(1);
	}
	path = NULL;
	i = 0;
	while (envp[i] && ft_strncmp("PATH=", envp[i], 4))
		i++;
	if (px->args)
		path = path_parser(envp[i] + 5, px->args[0]);
	if (path)
		execve(path, px->args, envp);
	close_fd(&px->pipe_fd[1]);
	free_args(px->args);
	if (!path)
		exit(127);
	error_printer(path);
	return (free(path), exit(126));
}

int	child_process(t_env **envp, t_pipex *px)
{
	char	**envp_string_form;

	if (manage_infile(px, STDIN_FILENO) || manage_outfile(px, STDOUT_FILENO))
		return (exit(1), 1);
	if (call_built_ins(envp, px->args) != -1)
	{
		close_fd(&px->pipe_fd[1]);
		free_args(px->args);
		return (ft_exit(envp, NULL));
	}
	envp_string_form = env_create(*envp);
	if (envp_string_form)
		executor(envp_string_form, px);
	exit(ft_exit(envp, NULL));
}

int	ft_built_ins(t_env **envp, t_pipex *px)
{
	int stdin_backup = dup(STDIN_FILENO);
	int stdout_backup = dup(STDOUT_FILENO);

	if (stdin_backup < 0 || stdout_backup < 0)
		return (error_printer("dup: backup failed"), 1);
	if (manage_infile(px, STDIN_FILENO) || manage_outfile(px, STDOUT_FILENO))
	{
		close_fd(&stdin_backup);
		close_fd(&stdout_backup);
		return (1);
	}
	call_built_ins(envp, px->args);
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close_fd(&stdin_backup);
	close_fd(&stdout_backup);
	return (0);
}

int	pipex(t_env **envp, t_pipex *px)
{
	int	pid;

	if (pipe(px->pipe_fd) == -1)
		return (perror("pipe: error"), 1);
	if (px->n_pids == 0 && !px->cmd->pipe_cmd
		&& (!ft_strcmp("cd", px->args[0]) || !ft_strcmp("env", px->args[0])
		|| !ft_strcmp("echo", px->args[0]) || !ft_strcmp("export", px->args[0])
		|| !ft_strcmp("pwd", px->args[0]) || !ft_strcmp("unset", px->args[0])
		|| !ft_strcmp("exit", px->args[0])))
		ft_built_ins(envp, px);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			close_fd(&px->pipe_fd[0]);
			child_process(envp, px);
			exit (EXIT_FAILURE);
		}
		else if (pid < 0)
			return (close_pipe(px), error_printer("fork: error"), 1);
		px->pids[px->n_pids++] = pid;
	}
	if (close_fd(&px->pipe_fd[1]) == -1
		|| (px->infile > 0 && close_fd(&px->infile) == -1))
		return (-1);
	return (px->infile = px->pipe_fd[0], px->pipe_fd[0] = -1, 0);
}

int	cmd_executor(t_env **envp, t_cmd **cmd)
{
	t_pipex	px;
	int		exit_status;

	if (!envp || !(*cmd))
		return (1);
	if (init_px(cmd, &px))
		return (1);
	while (px.cmd)
	{
		if (pipex(envp, &px))
			return (close_pipe(&px), 1);
		//fprintf(stderr, "		px->here_doc_fd = %i || px->pipe_fd[0] = %i || px->pipe_fd[1] = %i\n\
		//px->outfile = %i || px->infile = %i\n\
		//args[0] = %s || t_cmd = %p || pid = %i || n_pid = %i\n", px.here_doc_fd, \
		//px.pipe_fd[0], px.pipe_fd[1], px.outfile, \
		//px.infile, px.args[0], px.cmd, px.pids[0], px.n_pids);
		if (update_px(&px))
			return (1);
	}
	exit_status = 0;
	if (px.n_pids)
		exit_status = wait_execs(envp, &px);
	close_pipe(&px);
	return (exit_status);
}
