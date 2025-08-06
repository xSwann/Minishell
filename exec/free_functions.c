/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flebrun <flebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 13:54:16 by flebrun           #+#    #+#             */
/*   Updated: 2025/08/06 13:55:32 by flebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

int	loop_duplicate(t_env **envp, char **env_str)
{
	int		i;
	int		is_exit_code;
	char	*str_key;

	i = -1;
	is_exit_code = 0;
	while ((*envp)[++i].key)
	{
		if (!ft_strcmp((*envp)[i].key, "EXIT_CODE") && ++is_exit_code)
			continue ;
		str_key = ft_strjoin((*envp)[i].key, "=");
		if (!str_key)
			return (free_array(env_str), 1);
		env_str[i - is_exit_code] = ft_strjoin(str_key, (*envp)[i].value);
		if (!env_str[i - is_exit_code])
			return (free(str_key), free_array(env_str), 1);
		free(str_key);
		str_key = NULL;
	}
	return (0);
}

char	**free_array(char **array)
{
	int	i;

	if (!array)
		return (NULL);
	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i++] = NULL;
	}
	free(array);
	return (NULL);
}

t_cmd	*free_cmd(t_cmd *cmd)
{
	t_cmd	*prev_cmd;
	int		i;

	i = 0;
	prev_cmd = NULL;
	if (!cmd)
		return (NULL);
	cmd->args = free_array(cmd->args);
	cmd->infiles = free_array(cmd->infiles);
	cmd->outfiles = free_array(cmd->outfiles);
	if (cmd->here_doc_fds)
	{
		while (cmd->here_doc_fds[i])
			close_fd(&cmd->here_doc_fds[i++]);
		free(cmd->here_doc_fds);
		cmd->here_doc_fds = NULL;
	}
	prev_cmd = cmd;
	cmd = cmd->pipe_cmd;
	free(prev_cmd);
	prev_cmd = NULL;
	return (cmd);
}

int	close_pipe(t_pipex *px)
{
	if (close_fd(&px->pipe_fd[0]))
		return (close_fd(&px->pipe_fd[1]), \
		error_printer("close", "pipe_fd[0]"));
	if (close_fd(&px->pipe_fd[1]))
		return (error_printer("close", "pipe_fd[1]"));
	return (0);
}
