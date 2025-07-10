
#include "../includes/parsing.h"

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
		if (tokens[i].type == PIPE || tokens[i].type == REDOUT
			|| tokens[i].type == APPEND)
			break ;
		if (tokens[i].type == WORD
			&& (!(prev_type == HEREDOC || prev_type == REDIN)))
			n_args++;
		i++;
	}
	if (n_args == 0)
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
	cmd->pipe_cmd = 0;
	cmd->here_doc_fd = 0;
	cmd->args = cmd_init(tokens);
	cmd->open_options = O_WRONLY | O_CREAT | O_TRUNC;
	return (cmd);
}

void	handle_token(t_cmd *cmd, t_token token, int *n_args, t_type prev_type)
{
	t_type	curr_type;

	curr_type = token.type;
	if (curr_type == WORD)
	{
		if (prev_type == HEREDOC)
			cmd->here_doc_fd = ft_here_doc(ft_strdup(token.word));
		else if (prev_type == REDIN)
			cmd->infile = ft_strdup(token.word);
		else if (prev_type == REDOUT || prev_type == APPEND)
			cmd->outfile = ft_strdup(token.word);
		else
			cmd->args[(*n_args)++] = ft_strdup(token.word);
		free(token.word);
		token.word = NULL;
	}
	if (prev_type == REDOUT)
		cmd->open_options = O_WRONLY | O_CREAT | O_TRUNC;
	if (prev_type == APPEND)
		cmd->open_options = O_WRONLY | O_CREAT | O_APPEND;
}

int	cmd_creator(t_cmd **cmd, t_token *tokens)
{
	int			i;
	int			n_args;
	t_type		prev_type;

	i = 0;
	n_args = 0;
	prev_type = INVALID;
	if (!tokens || tokens[i].type == END)
		return ((*cmd) = NULL, 0);
	*cmd = init_command(tokens);
	if (!*cmd)
		return (1);
	while (tokens[i].type != END)
	{
		if (prev_type == PIPE)
		{
			if (cmd_creator(&(*cmd)->pipe_cmd, tokens + i))
				return (1);
			return (0);
		}
		handle_token(*cmd, tokens[i], &n_args, prev_type);
		prev_type = tokens[i++].type;
	}
	return (0);
}

void	print_cmd(t_cmd *cmd)
{
	int	i;
	int	n_cmd;

	n_cmd = 0;
	if (cmd)
	{
		i = -1;
		fprintf(stderr, "		|||  print_cmd  |||\n");
		while (++i >= 0 && cmd->args && cmd->args[i])
			fprintf(stderr, "cmd->args[%i] = %s\n", i, cmd->args[i]);
		fprintf(stderr, "cmd->infile = %s\ncmd->outfile = %s\n\
		cmd->open_options = %i\ncmd->fd_here_doc = %i\ncmd->pipe_cmd = %p\n", \
		cmd->infile, cmd->outfile, cmd->open_options, cmd->here_doc_fd, \
		cmd->pipe_cmd);
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
