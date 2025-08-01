/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_manipulations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flebrun <flebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:00:26 by flebrun           #+#    #+#             */
/*   Updated: 2025/08/01 15:48:33 by flebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built_ins.h"
#include "../includes/parsing.h"
#include <readline/readline.h>
#include <unistd.h>

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

int	close_fd(int *fd)
{
	if (fd && *fd >= 0)
	{
		if (close(*fd) == -1)
			return (*fd = -1, error_printer("close", "failed closing fd"), 1);
		*fd = -1;
	}
	return (0);
}

void	kill_here_doc(int signal)
{
	if (signal == SIGINT)
	{
		g_receive_sig++;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		close(STDIN_FILENO);
	}
}

void	loop_readline(t_env **env, char *limiter, int pipe_fd[2])
{
	int		sig_backup;
	char	*line;
	
	sig_backup = g_receive_sig;
	while (1)
	{
		line = readline("> ");
		if (g_receive_sig > sig_backup && g_receive_sig--)
		{
			ft_export(env, "EXIT_CODE=130");
			close_fd(&pipe_fd[0]);
			break ;
		}
		if (!line || ft_strcmp(line, limiter) == 0)
			break ;
		if (line[0])
			add_history(line);
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
		line = NULL;
	}
	if (line)
		free(line);
}

int	ft_here_doc(t_env **env, char *limiter)
{
	int	pipe_fd[2];
	int	stdin_backup;

	stdin_backup = dup(STDIN_FILENO);
	signal(SIGINT, kill_here_doc);
	if (!limiter)
		return (1);
	if (pipe(pipe_fd) == -1)
		return (free(limiter), error_printer("pipe", "error"), -1);
	loop_readline(env, limiter, pipe_fd);
	dup2(stdin_backup, STDIN_FILENO);
	close(stdin_backup);
	signal(SIGINT, signalhandler);
	free(limiter);
	limiter = NULL;
	return (close_fd(&pipe_fd[1]), pipe_fd[0]);
}
