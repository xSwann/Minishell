/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_manipulations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flebrun <flebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:00:26 by flebrun           #+#    #+#             */
/*   Updated: 2025/06/27 09:50:14 by flebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	error_printer(char *path)
{
	write(2, "pipex: ", 7);
	write(2, strerror(errno), strlen(strerror(errno)));
	write(2, ": ", 2);
	write(2, path, strlen(path));
	return (write(2, "\n", 1));
}

int	close_fd(int *fd)
{
	if (fd && *fd >= 0)
	{
		if (close(*fd) == -1)
			return (*fd = -1, error_printer("close: failed closing fd"), 1);
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
		return (free(limiter), error_printer("pipe: error"), -1);
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
	free(line);
	return (line = NULL, close_fd(&pipe_fd[1]), pipe_fd[0]);
}
