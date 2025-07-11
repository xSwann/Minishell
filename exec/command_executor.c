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

int	call_built_ins(t_env **envp, char **cmd)
{
	if (!envp || !(*envp)->key || !cmd || !*cmd)
		return (0);
	else if (!ft_strcmp("cd", cmd[0]))
		return (ft_cd(cmd, envp));
	else if (!ft_strcmp("env", cmd[0]))
		return (ft_env(envp));
	else if (!ft_strcmp("echo", cmd[0]))
		return (ft_echo(cmd + 1, envp), 1);
	else if (!ft_strcmp("export", cmd[0]))
		return (ft_export(envp, cmd[1]));
	else if (!ft_strcmp("pwd", cmd[0]))
		return (ft_pwd(envp));
	else if (!ft_strcmp("unset", cmd[0]))
		return (ft_unset(envp, cmd[1]));
	else if (!ft_strcmp("exit", cmd[0]))
		return (ft_exit(envp, cmd));
	return (-1);
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
	int	stdin_backup;
	int	stdout_backup;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (manage_infile(px, stdin_backup) || manage_outfile(px, stdout_backup))
		return (exit(1), 1);
	call_built_ins(envp, px->args);
	if (px->infile && dup2(stdin_backup, px->infile) == -1 
		&& error_printer("dup2: error"))
		return (close_pipe(px), 1);
	if (px->outfile && dup2(stdout_backup, px->outfile) == -1 
		&& error_printer("dup2: error"))
		return (close_pipe(px), 1);
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
		if (update_px(&px))
			return (1);
	}
	//fprintf(stderr, "		px->here_doc_fd = %i || px->pipe_fd[0] = %i || px->pipe_fd[1] = %i\n\
	//	px->outfile = %i || px->prev_fd = %i || px->infile = %i\n\
	//	args[0] = %s || t_cmd = %p || pid = %i || n_pid = %i\n", px.here_doc_fd, \
	//	px.pipe_fd[0], px.pipe_fd[1], px.outfile, px.prev_fd, \
	//	px.infile, px.args[0], px.cmd, px.pids[0], px.n_pids);
	exit_status = wait_execs(envp, &px);
	//if (dup2(px.stdin_backup, STDIN_FILENO) == -1)
	//	error_printer("dup2: stdin");
	close_pipe(&px);
	return (exit_status);
}
