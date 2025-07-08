#include "../includes/exec.h"
#include <unistd.h>

void	executor(char **envp, t_pipex *px)
{
	char	*path;
	int		i;

	close_fd(&px->pipe_fd[0]);
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

int	is_built_ins(t_env **envp, char **cmd)
{
	if (!envp || !(*envp)->key || !cmd || !*cmd)
		return (0);
	else if (!ft_strcmp("cd", cmd[0]))
		return (ft_cd(cmd[1], envp));
	else if (!ft_strcmp("env", cmd[0]))
		return (ft_env(envp));
	else if (!ft_strcmp("echo", cmd[0]))
		return (ft_echo(cmd + 1, 0, envp));
	else if (!ft_strcmp("export", cmd[0]))
		return (ft_export(envp, cmd[1]));
	else if (!ft_strcmp("pwd", cmd[0]))
		return (ft_pwd(envp));
	else if (!ft_strcmp("unset", cmd[0]))
		return (ft_unset(envp, cmd[1]));
	return (-1);
}

int	child_process(t_env **envp, t_pipex *px)
{
	char	**envp_string_form;

	if (px->prev_fd > 0)
	{
		if ((dup2(px->prev_fd, 0) == -1 && error_printer("dup2: error")
				&& close_pipe(px) < 2) || close_fd(&px->prev_fd) == -1)
			return (exit(1), 1);
	}
	if (!px->outfile)
	{
		if ((dup2(px->pipe_fd[1], 1) == -1 && error_printer("dup2: error")
				&& close_pipe(px) < 2) || close_fd(&px->pipe_fd[1]) == -1)
			return (exit(1), 1);
	}
	if (is_built_ins(envp, px->args) != -1)
		exit(1);
	envp_string_form = env_create(*envp);
	if (envp_string_form)
		executor(envp_string_form, px);
	exit(1);
}

int	pipex(t_env **envp, t_pipex *px)
{
	int	pid;

	if (pipe(px->pipe_fd) == -1)
		return (perror("pipe: error"), 1);
	pid = fork();
	if (pid == 0)
	{
		child_process(envp, px);
		return (1);
	}
	else if (pid < 0)
		return (close_pipe(px), error_printer("fork: error"), 1);
	px->pids[px->n_pids++] = pid;
	if (close_fd(&px->pipe_fd[1]) == -1)
		return (-1);
	if (px->infile == px->prev_fd)
		px->infile = -1;
	if (close_fd(&px->prev_fd) == -1)
		return (1);
	return (px->prev_fd = px->pipe_fd[0], px->pipe_fd[0] = -1, 0);
}

int	cmd_executor(t_env **envp, t_cmd **cmd)
{
	t_pipex	px;
	int		exit_status;

	if (!envp || !(*cmd))
		return (1);
	px.stdin_backup = 0;
	px.stdout_backup = 0;
	if (init_px(cmd, &px))
		return (1);
	while (px.cmd)
	{
		if (pipex(envp, &px))
			return (close_pipe(&px), 1);
		if (update_px(&px))
			return (1);
	}
	//fprintf(stderr, "		px->here_doc_fd = %i || px->pipe_fd[0] = %i || px->pipe_fd[1] = %i\n\
	//	px->outfile = %i || px->prev_fd = %i || px->infile = %i\n\
	//	args[0] = %s || t_cmd = %p || pid = %i || n_pid = %i\n", px.here_doc_fd, \
	//	px.pipe_fd[0], px.pipe_fd[1], px.outfile, px.prev_fd, \
	//	px.infile, px.args[0], px.cmd, px.pids[0], px.n_pids);
	exit_status = wait_execs(px.pids, px.n_pids);
	close_pipe(&px);
	if (px.outfile >= 0)
		close_fd(&px.outfile);
	fd_std_handler(&px); 
	return (exit_status);
}
