/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure_manipulations.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flebrun <flebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:57:03 by flebrun           #+#    #+#             */
/*   Updated: 2025/07/06 17:02:35 by flebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

int	free_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return (1);
	while (args[i])
		free(args[i++]);
	return (free(args), 1);
}

int	manage_outfile(t_pipex *px)
{
	if (px->outfile < 0)
		return (px->outfile = -1, close_pipe(px), 1);
	if (dup2(px->outfile, 1) == -1 && error_printer("dup2: error"))
		return (close_fd(&px->outfile), close_pipe(px), 1);
	if (close_fd(&px->outfile) == -1)
		return (close_pipe(px), 1);
	return (0);
}

t_cmd	*free_cmd(t_cmd **cmd)
{
	int		i;
	t_cmd	*pipe_cmd;

	pipe_cmd = NULL;
	if (!(*cmd))
		return (pipe_cmd);
	if ((*cmd)->args)
	{
		i = 0;
		while ((*cmd)->args[i])
		{
			free((*cmd)->args[i]);
			(*cmd)->args[i++] = NULL;
		}
		free((*cmd)->args);
		(*cmd)->args = NULL;
	}
	if ((*cmd)->infile)
	{
		free((*cmd)->infile);
		(*cmd)->infile = NULL;
	}
	if ((*cmd)->outfile)
	{
		free((*cmd)->outfile);
		(*cmd)->outfile = NULL;
	}
	pipe_cmd = (*cmd)->pipe_cmd;
	free(*cmd);
	return (pipe_cmd);
}

int	init_px(t_cmd **cmd, t_pipex *px, int stdin, int stdout)
{
	if (!cmd || !(*cmd))
		return (fprintf(stderr, "\n\ninit_px : cmd is NULL\n\n"));
	px->infile = stdin;
	px->outfile = stdout;
	px->here_doc_fd = 0;
	px->pid = 0;
	px->pipe_fd[0] = -1;
	px->pipe_fd[1] = -1;
	px->prev_fd = px->infile;
	px->args = (*cmd)->args;
	px->cmd = *cmd;
	if ((*cmd)->here_doc_fd && fprintf(stderr, "\n\nhere_doc detected\n\n"))
		px->infile = (*cmd)->here_doc_fd;
	else if (!(*cmd)->here_doc_fd && (*cmd)->infile)
		px->infile = open((*cmd)->infile, O_RDONLY);
	if (px->infile < 0)
		return (error_printer((*cmd)->infile), 1);
	if ((*cmd)->outfile)
	{
		if ((*cmd)->open_options == (O_WRONLY | O_CREAT | O_TRUNC))
			px->outfile = open((*cmd)->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if ((*cmd)->open_options == (O_WRONLY | O_CREAT | O_APPEND))
			px->outfile = open((*cmd)->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (px->outfile < 0)
			return (error_printer((*cmd)->outfile), 1);
	}
	else if (!(*cmd)->outfile && (*cmd)->pipe_cmd)
		(*cmd)->outfile = (*cmd)->pipe_cmd->infile;
	//fprintf(stderr, "		px->here_doc_fd = %i || px->pipe_fd[0] = %i || px->pipe_fd[1] = %i\n\
	//	px->outfile = %i || px->prev_fd = %i || px->infile = %i\n\
	//	args[0] = %s || t_cmd = %p || pid = %i\n", px->here_doc_fd, \
	//	px->pipe_fd[0], px->pipe_fd[1], px->outfile, px->prev_fd, \
	//	px->infile, px->args[0], px->cmd, px->pid);
	return (px->pid = 0, 0);
}
