/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_creator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flebrun <flebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 13:54:43 by flebrun           #+#    #+#             */
/*   Updated: 2025/08/06 14:57:25 by flebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int	arrays_malloc(t_cmd *cmd)
{
	if (cmd->counters[0])
		cmd->args = (char **)ft_calloc(cmd->counters[0] + 2, sizeof(char *));
	if (cmd->counters[0] && !cmd->args)
		return (1);
	cmd->counters[0] = 0;
	if (cmd->counters[1])
		cmd->infiles = (char **)ft_calloc(cmd->counters[1] + 1, sizeof(char *));
	if (cmd->counters[1] && !cmd->infiles)
		return (free(cmd->args), 1);
	cmd->counters[1] = 0;
	if (cmd->counters[2])
		cmd->outfiles = (char **)ft_calloc(cmd->counters[2] + 1, \
		sizeof(char *));
	if (cmd->counters[2] && !cmd->outfiles)
		return (free(cmd->args), free(cmd->infiles), 1);
	cmd->counters[2] = 0;
	if (cmd->counters[3])
		cmd->here_doc_fds = (int *)ft_calloc(cmd->counters[3] + 1, \
		sizeof(int));
	if (cmd->counters[3] && !cmd->here_doc_fds)
		return (free(cmd->args), free(cmd->infiles), free(cmd->outfiles), 1);
	cmd->counters[3] = 0;
	return (0);
}

int	arrays_init(t_token *tokens, t_cmd *cmd)
{
	int		i;

	i = -1;
	while (tokens[++i].type != END)
	{
		if (tokens[i].type == WORD && tokens[i].word
			&& cmd->prev_type == REDIN && !cmd->open_errors)
			cmd->counters[1]++;
		else if ((tokens[i].type == WORD && tokens[i].word
				&& (cmd->prev_type == REDOUT || cmd->prev_type == APPEND)
				&& !cmd->open_errors) && ++cmd->counters[2])
		{
			if (access(tokens[i].word, F_OK) == 0
				&& access(tokens[i].word, W_OK) == -1)
				cmd->open_errors = 1;
		}
		else if (cmd->prev_type == HEREDOC)
			cmd->counters[3]++;
		else if (tokens[i].type == WORD && tokens[i].word)
			cmd->counters[0]++;
		else if (tokens[i].type == PIPE && cmd->counters[0])
			break ;
		cmd->prev_type = tokens[i].type;
	}
	return (arrays_malloc(cmd));
}

t_cmd	*init_command(t_gc *cmd_gc, t_env **env, t_token *tokens)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->pipe_cmd = 0;
	cmd->args = NULL;
	cmd->infiles = NULL;
	cmd->outfiles = NULL;
	cmd->here_doc_fds = NULL;
	cmd->counters[0] = 0;
	cmd->counters[1] = 0;
	cmd->counters[2] = 0;
	cmd->counters[3] = 0;
	cmd->prev_type = INVALID;
	if (arrays_init(tokens, cmd))
		return (NULL);
	cmd->open_options = O_WRONLY | O_CREAT | O_TRUNC;
	if (cmd_gc->actual_i == 0)
	{
		cmd_gc->tokens = tokens;
		cmd_gc->first_cmd = cmd;
		cmd_gc->env = env;
	}
	return (cmd->open_errors = 0, cmd);
}

int	handle_token(t_cmd *cmd, t_gc *gc, t_token *tkn)
{
	if (tkn->type == WORD && tkn->word)
	{
		if (cmd->prev_type == HEREDOC)
		{
			cmd->here_doc_fds[cmd->counters[3]] = ft_here_doc(gc);
			if (cmd->here_doc_fds[cmd->counters[3]++] <= 0)
				cmd->counters[3]--;
		}
		else if (cmd->prev_type == REDIN)
			cmd->infiles[cmd->counters[1]++] = ft_strdup(tkn->word);
		else if (cmd->prev_type == REDOUT || cmd->prev_type == APPEND)
		{
			cmd->outfiles[cmd->counters[2]++] = ft_strdup(tkn->word);
			if (access(tkn->word, F_OK) == 0 && access(tkn->word, W_OK) == -1)
				return (free(tkn->word), tkn->word = NULL, 1);
		}
		else
			cmd->args[cmd->counters[0]++] = ft_strdup(tkn->word);
	}
	if (cmd->prev_type == REDOUT)
		cmd->open_options = O_WRONLY | O_CREAT | O_TRUNC;
	if (cmd->prev_type == APPEND)
		cmd->open_options = O_WRONLY | O_CREAT | O_APPEND;
	return (free(tkn->word), tkn->word = NULL, 0);
}

int	cmd_creator(t_env **env, t_cmd **cmd, t_token *tokens)
{
	t_gc	cmd_gc;
	t_cmd	*curr_cmd;

	cmd_gc.actual_i = 0;
	if (!tokens || tokens[0].type == END)
		return ((*cmd) = NULL, 0);
	*cmd = init_command(&cmd_gc, env, tokens);
	if (!*cmd)
		return (1);
	curr_cmd = *cmd;
	while (tokens[cmd_gc.actual_i].type != END)
	{
		if (curr_cmd->prev_type == PIPE)
		{
			curr_cmd->pipe_cmd = init_command(&cmd_gc, env, \
				tokens + cmd_gc.actual_i);
			if (!curr_cmd->pipe_cmd)
				return (1);
			curr_cmd = curr_cmd->pipe_cmd;
			curr_cmd->prev_type = tokens[cmd_gc.actual_i].type;
		}
		handle_token(curr_cmd, &cmd_gc, &tokens[cmd_gc.actual_i]);
		curr_cmd->prev_type = tokens[cmd_gc.actual_i++].type;
	}
	return (0);
}
