#include "../includes/exec.h"

void	executor(char *shell_name, t_env **env, char **args)
{
	char	**env_str;
	int		status;
	char	*path;

	path = NULL;
	status = path_parser(shell_name, env, args, &path);
	if (status != CMD_OK && path)
	{
		free(path);
		path = NULL;
	}
	env_str = env_create(env);
	if (!env_str && error_printer("envp not found", NULL))
		return (free_array(args), exit(126));
	if (status == CMD_OK && execve(path, args, env_str))
	{
		if (errno == ENOENT)
		{
			error_printer(args[0], "No such file or directory");
			exit(127);
		}
		else if (errno == EISDIR)
			error_printer(args[0], "Is a directory");
		else if (errno == EACCES)
			error_printer(args[0], "Permission denied");
		else
			perror("execve");
	}
	free_array(env_str);
	free_array(args);
	if (status == CMD_NOT_FOUND)
		return (exit(127));
	return (exit(126));
}

int	child_process(t_env **envp, t_pipex *px)
{
	char	**args_ptr;
	int		i;
	
	free(px->pids);
	if (manage_infile(px, STDIN_FILENO) || manage_outfile(px, STDOUT_FILENO))
	{
		while (px->cmd)
			px->cmd = free_cmd(px->cmd);
		return (free_env(envp), close_pipe(px), exit(1), 0);
	}
	args_ptr = px->cmd->args;
	px->cmd->args = NULL;
	while (px->cmd)
		px->cmd = free_cmd(px->cmd);
	if ((i = check_built_ins(args_ptr)) > 0)
	{
		call_built_ins(envp, args_ptr, i);
		free_array(args_ptr);
	}
	else
		executor(px->shell_name, envp, args_ptr);
	close_fd(&px->outfile);
	ft_exit(envp, NULL);
	exit (1);
}

int	ft_built_ins(t_env **envp, t_pipex *px, int i)
{
	int stdin_backup;
	int stdout_backup;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (stdin_backup < 0 || stdout_backup < 0)
		return (error_printer("dup", "backup failed"), 1);
	if (manage_infile(px, STDIN_FILENO) || manage_outfile(px, STDOUT_FILENO))
	{
		close_fd(&stdin_backup);
		close_fd(&stdout_backup);
		return (ft_export(envp, "EXIT_CODE=1"), 1);
	}
	call_built_ins(envp, px->cmd->args, i);
	if (dup2(stdin_backup, STDIN_FILENO) == -1
		|| dup2(stdout_backup, STDOUT_FILENO) == -1
		|| close_fd(&stdin_backup) || close_fd(&stdout_backup))
		return (error_printer("dup2", "restore failed"));
	return (0);
}

int	pipex(t_env **envp, t_pipex *px)
{
	int	pid;

	if (pipe(px->pipe_fd) == -1)
		return (perror("pipe: error"), 1);
	pid = check_built_ins(px->cmd->args);
	if (px->n_pids == 0 && !px->cmd->pipe_cmd
		&& px->cmd->args && px->cmd->args[0] && (pid > 0 && pid < 6))
		ft_built_ins(envp, px, pid);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			child_process(envp, px);
			exit (EXIT_FAILURE);
		}
		else if (pid < 0)
			return (close_pipe(px), error_printer("fork", "error"), 1);
		px->pids[px->n_pids++] = pid;
	}
	if (close_fd(&px->pipe_fd[1]) == -1
		|| (px->infile > 0 && close_fd(&px->infile) == -1))
		return (-1);
	return (px->infile = px->pipe_fd[0], px->pipe_fd[0] = -1, 0);
}

int	cmd_executor(char *shell_name, t_env **envp, t_cmd **cmd)
{
	t_pipex	px;
	int		exit_status;

	if (!envp || !(*cmd))
		return (1);
	if (init_px(shell_name, cmd, &px))
		return (1);
	while (px.cmd)
	{
		if (pipex(envp, &px))
			return (close_pipe(&px), 1);
		if (!px.cmd->pipe_cmd)
			break ;
		if (update_px(&px))
			return (1);
	}
	exit_status = 0;
	if (px.n_pids)
		exit_status = wait_execs(envp, &px);
	free_cmd(px.cmd);
	close_pipe(&px);
	close_fd(&px.infile);
	//close_fd(&px.outfile);
	return (exit_status);
}
		//fprintf(stderr, "		px->here_doc_fd = %i || px->pipe_fd[0] = %i || px->pipe_fd[1] = %i\n\
		//px->outfile = %i || px->infile = %i\n\
		//args[0] = %s || t_cmd = %p || pid = %i || n_pid = %i\n", px.here_doc_fd, \
		//px.pipe_fd[0], px.pipe_fd[1], px.outfile, \
		//px.infile, px.args[0], px.cmd, px.pids[0], px.n_pids);
