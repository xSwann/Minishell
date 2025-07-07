#include "../includes/exec.h"

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

int	child_process(t_env **envp, t_pipex *px)
{
	char	**envp_string_form;

	if (px->prev_fd >= 0)
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
	else if (px->outfile && manage_outfile(px))
		return (exit(1), 1);
	envp_string_form = env_create(*envp);
	if (envp_string_form)
		executor(envp_string_form, px);
	exit(1);
}

int	is_built_ins(t_env **envp, char **cmd)
{
	if (!envp || !(*envp)->key || !cmd || !*cmd)
		return (0);
	else if (!ft_strcmp("cd", cmd[0]) && fprintf(stderr, "built-ins %s appelle\n", cmd[0]))
		return (/*ft_cd(envp, cmd[1]), */1);
	else if (!ft_strcmp("env", cmd[0]) && fprintf(stderr, "built-ins %s appelle\n", cmd[0]))
		return (/*ft_env(envp), */1);
	else if (!ft_strcmp("echo", cmd[0]) && fprintf(stderr, "built-ins %s appelle\n", cmd[0]))
		return (/*ft_env(envp, cmd + 1), */1);
	else if (!ft_strcmp("export", cmd[0]) && fprintf(stderr, "built-ins %s appelle\n", cmd[0]))
		return (/*ft_export(envp, cmd[1]), */1);
	else if (!ft_strcmp("pwd", cmd[0]) && fprintf(stderr, "built-ins %s appelle\n", cmd[0]))
		return (/*ft_pwd(envp), */1);
	else if (!ft_strcmp("unset", cmd[0]) && fprintf(stderr, "built-ins %s appelle\n", cmd[0]))
		return (/*ft_unset(envp, cmd[1]), */1);
	return (0);
}

int	pipex(t_env **envp, t_pipex *px)
{
	int	pid;

	if (pipe(px->pipe_fd) == -1)
		return (perror("pipe: error"), 1);
	if (px && px->args && px->args[0] && is_built_ins(envp, px->args))
		return (px->pid = -1, 0);
	pid = fork();
	if (pid == 0)
	{
		child_process(envp, px);
		return (1);
	}
	else if (pid < 0)
		return (close_pipe(px), error_printer("fork: error"), 1);
	px->pid = pid;
	if (close_fd(&px->pipe_fd[1]) == -1)
		return (-1);
	if (px->infile == px->prev_fd)
		px->infile = -1;
	if (close_fd(&px->prev_fd) == -1)
		return (1);
	return (px->prev_fd = px->pipe_fd[0], 0);
}

int	cmd_executor(t_env **envp, t_cmd **cmd)
{
	t_pipex	px;
	int		exit_status;
	int		stdin_backup;
	int		stdout_backup;

	if (!envp || !(*cmd))
		return (1);
	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	while ((*cmd))
	{
		//fprintf(stderr, "\n\nbefore, cmd is %p\n\n", (*cmd));
		if (init_px(cmd, &px, stdin_backup, stdout_backup))
			return (1);
		if (pipex(envp, &px))
			return (close_pipe(&px), 1);
		*cmd = free_cmd(cmd);
		//fprintf(stderr, "\n\nafter, cmd is %p\n\n", (*cmd));
	}
	exit_status = wait_execs(px.pid);
	close_pipe(&px);
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	if (px.outfile >= 0)
		close_fd(&px.outfile);
	return (close(stdin_backup), close(stdout_backup), exit_status);
}
