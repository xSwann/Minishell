/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_manipulations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flebrun <flebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:00:26 by flebrun           #+#    #+#             */
/*   Updated: 2025/08/06 13:56:34 by flebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built_ins.h"
#include "../includes/parsing.h"
#include "../includes/exec.h"
#include <readline/readline.h>

int	error_printer(char *str1, char *str2)
{
	int	errno_backup;

	errno_backup = errno;
	write(2, "minishell: ", 11);
	if (str1 && *str1)
	{
		write(2, str1, strlen(str1));
		write(2, ": ", 2);
	}
	if (errno_backup == EISDIR)
		return (write(2, "Is a directory\n", 15));
	if (!str2 && errno_backup == ENOENT)
		return (write(2, "No such file or directory\n", 27));
	else if (!str2 && errno_backup == EACCES)
		return (write(2, "Permission denied\n", 19));
	if (str2 && *str2)
		write(2, str2, strlen(str2));
	else
		write(2, strerror(errno_backup), strlen(strerror(errno_backup)));
	return (write(2, "\n", 1));
}

int	here_doc_wait(t_env **envp, int pid)
{
	int		status;
	int		exit_code;
	char	*status_str;
	char	*exit_str;

	exit_code = 0;
	if (waitpid(pid, &status, 0) == -1)
		error_printer("waitpid failed", NULL);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	status_str = ft_itoa(exit_code);
	if (!status_str)
		return (exit_code);
	exit_str = ft_strjoin("EXIT_CODE=", status_str);
	free(status_str);
	if (!exit_str)
		return (exit_code);
	return (ft_export(envp, exit_str), free(exit_str), exit_code);
}

int	here_doc_loop(char *limiter, int pipe_fd[2])
{
	char	*line;

	g_receive_sig = 2;
	close_fd(&pipe_fd[0]);
	while (1)
	{
		line = readline("> ");
		if (!line || g_receive_sig == 3 || !ft_strcmp(line, limiter))
			break ;
		if (*line)
			add_history(line);
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
		line = NULL;
	}
	rl_clear_history();
	free(limiter);
	limiter = NULL;
	if (line)
		free(line);
	return (line = NULL, close_fd(&pipe_fd[1]), exit(g_receive_sig == 3), 1);
}

void	free_gc(t_gc *gc)
{
	while (gc->tokens[gc->actual_i].word)
	{
		free(gc->tokens[gc->actual_i].word);
		gc->tokens[gc->actual_i++].word = NULL;
	}
	free(gc->tokens);
	gc->tokens = NULL;
	while (gc->first_cmd)
		gc->first_cmd = free_cmd(gc->first_cmd);
	free_env(gc->env);
	rl_clear_history();
	gc->env = NULL;
}

int	ft_here_doc(t_gc *gc)
{
	int		pipe_fd[2];
	int		pid;
	char	*limiter;

	if (pipe(pipe_fd) == -1)
		return (error_printer("pipe", "error"), -1);
	pid = fork();
	if (pid == 0)
	{
		limiter = ft_strdup(gc->tokens[gc->actual_i].word);
		free_gc(gc);
		here_doc_loop(limiter, pipe_fd);
		return (exit (1), 1);
	}
	else if (pid < 0)
		return (close_fd(&pipe_fd[0]), close_fd(&pipe_fd[1]), error_printer("fork", "error"), 1);
	signal(SIGINT, SIG_IGN);
	if (here_doc_wait(gc->env, pid))
		close_fd(&pipe_fd[0]);
	signal(SIGINT, signalhandler);
	return (close_fd(&pipe_fd[1]), pipe_fd[0]);
}
