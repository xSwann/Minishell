#include "parsing.h"

t_cmd	*free_cmd(t_cmd *cmd)
{
	int		i;
	t_cmd	*pipe_cmd;

	i = 0;
	pipe_cmd = NULL;
	if (!cmd)
		return (pipe_cmd);
	if (cmd->args)
	{
		/*while (cmd->args[i])
		{
			printf("PIGNOUF\n");
			free(cmd->args[i]);
			i++;
		}*/
		free(cmd->args);
	}
	/*if (cmd->outfile)
		free(cmd->outfile);*/
	pipe_cmd = cmd->pipe_cmd;
	return (pipe_cmd);
}

char	**cmd_init(t_token *tokens)
{
	t_type	prev_type;
	char	**args;
	int		n_args;
	int		i;

	i = 0;
	n_args = 0;
	prev_type = INVALID;
	while (tokens[i].type != END)
	{
		if (tokens[i].type == PIPE
			|| tokens[i].type == REDOUT || tokens[i].type == APPEND)
			break ;
		if (tokens[i].type == WORD
			&& (!(prev_type == HEREDOC || prev_type == REDIN)))
			n_args++;
		i++;
	}
	if (!n_args)
		return (NULL);
	args = (char **)ft_calloc(n_args + 1, sizeof(char *));
	if (!args)
		return (NULL);
	return (args);
}

t_cmd	*init_command(t_token *tokens)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = cmd_init(tokens);
	return (cmd);
}

void	handle_token(t_cmd *cmd, t_token token, int *n_args, t_type prev_type)
{
	t_type curr_type;

	curr_type = token.type;
	if (curr_type == WORD)
	{
		if (prev_type == REDIN || prev_type == HEREDOC)
		{
			cmd->is_here_doc = 1;
			cmd->infile = token.word;
		}
		else if (prev_type != REDOUT)
			cmd->args[(*n_args)++] = token.word;
	}
	else if (prev_type == REDOUT)
		cmd->open_options = O_WRONLY | O_CREAT | O_TRUNC;
	else if (prev_type == APPEND)
		cmd->open_options = O_WRONLY | O_CREAT | O_APPEND;
}

t_cmd	*cmd_creator(t_token *tokens)
{
	int			i;
	int			n_args;
	t_type		prev_type;
	t_cmd		*cmd;

	i = 0;
	n_args = 0;
	prev_type = INVALID;
	cmd = init_command(tokens);
	if (!cmd)
		return (NULL);
	while (!cmd->pipe_cmd && tokens[i].type != END)
	{
		if (prev_type == PIPE)
			cmd->pipe_cmd = cmd_creator(tokens + i);
		handle_token(cmd, tokens[i], &n_args, prev_type);
		prev_type = tokens[i++].type;
	}
	if (prev_type == WORD && !cmd->outfile)
		cmd->outfile = tokens[i - 1].word;
	return (cmd);
}

void	print_cmd(t_cmd *cmd)
{
	int	i;
	int	n_cmd;

	n_cmd = 0;
	while (cmd && cmd->args)
	{
		i = 0;
		printf("|||  print_cmd num %d   |||\n", n_cmd++);
		while (cmd->args[i])
		{
			printf("cmd->args[%i] = %s\n", i, cmd->args[i]);
			i++;
		}
		printf("cmd->infile = %s\ncmd->outfile = %s\ncmd->open_options = %i\ncmd->is_here_doc = %d\n", cmd->infile, cmd->outfile, cmd->open_options, cmd->is_here_doc);
		cmd = free_cmd(cmd);
	}
}

/* int	main(int ac, char **av)
{
	t_token	**tokens;
	t_cmd	*cmd;
	int		i;

	i = 0;
	tokens = malloc(sizeof(t_token *) * (ac / 2 + 1));
	while (i < ac / 2)
	{
		tokens[i / 2] = malloc(sizeof(t_token));
		tokens[i / 2]->word = av[i + 1];
		i++;
		tokens[i / 2]->type = av[i + 1][0] - '0';
		i++;
	}
	tokens[i / 2] = NULL;
	cmd = cmd_creator(tokens);
	print_cmd(cmd);
	free(tokens[0]);
	free(tokens);
	//cmd_executor(cmd);
	while (cmd && cmd->pipe_cmd)
	{
		prev_cmd = cmd;
		cmd = cmd->pipe_cmd;
		free(prev_cmd);
	}
} */
