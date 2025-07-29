/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_manipulations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flebrun <flebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:00:26 by flebrun           #+#    #+#             */
/*   Updated: 2025/07/29 13:48:01 by flebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"
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

int	ft_here_doc(char *limiter)
{
	int		pipe_fd[2];
	char	*line;

	if (!limiter)
		return (1);
	if (pipe(pipe_fd) == -1)
		return (free(limiter), error_printer("pipe", "error"), -1);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, limiter) == 0)
			break ;
		if (*line)
			add_history(line);
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
		line = NULL;
	}
	free(limiter);
	limiter = NULL;
	if (line)
		free(line);
	line = NULL;
	return (line = NULL, close_fd(&pipe_fd[1]), pipe_fd[0]);
}
