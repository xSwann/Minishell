
#include "../includes/parsing.h"

int	arrays_malloc(t_cmd *cmd)
{
	if (cmd->counters[0])
		cmd->args = (char **)ft_calloc(cmd->counters[0] + 1, sizeof(char *));
	if (cmd->counters[0] && !cmd->args)
		return (1);
	cmd->counters[0] = 0;
	if (cmd->counters[1])
		cmd->infiles = (char **)ft_calloc(cmd->counters[1] + 1, sizeof(char *));
	if (cmd->counters[1] && !cmd->infiles)
		return (free(cmd->args), 1);
	cmd->counters[1] = 0;
	if (cmd->counters[2])
		cmd->outfiles = (char **)ft_calloc(cmd->counters[2] + 1, sizeof(char *));
	if (cmd->counters[2] && !cmd->outfiles)
		return (free(cmd->args), free(cmd->infiles), 1);
	cmd->counters[2] = 0;
	return (0);
}

int	arrays_init(t_token *tokens, t_cmd *cmd)
{
	int		i;

	i = 0;
	while (tokens[i].type != END)
	{
		if (tokens[i].type == WORD && cmd->prev_type == REDIN)
			cmd->counters[1]++;
		else if (tokens[i].type == WORD &&
			(cmd->prev_type == REDOUT || cmd->prev_type == APPEND))
			cmd->counters[2]++;
		else if (tokens[i].type == WORD && !(cmd->prev_type == HEREDOC))
			cmd->counters[0]++;
		else if (tokens[i].type == PIPE && cmd->counters[0])
			break ;
		cmd->prev_type = tokens[i].type;
		i++;
	}
	if (arrays_malloc(cmd))
		return (1);
	return (0);
}

t_cmd	*init_command(t_token *tokens)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->pipe_cmd = 0;
	cmd->here_doc_fd = 0;
	cmd->args = NULL;
	cmd->infiles = NULL;
	cmd->outfiles = NULL;
	cmd->counters[0] = 0;//ARGS_COUNTER
	cmd->counters[1] = 0;//INFILES_COUNTER
	cmd->counters[2] = 0;//OUTFILES_COUNTER
	cmd->prev_type = INVALID;
	if (arrays_init(tokens, cmd))
		return (NULL);
	cmd->open_options = O_WRONLY | O_CREAT | O_TRUNC;
	return (cmd);
}

void	handle_token(t_env *env, t_cmd *cmd, t_token token)
{
	t_type	curr_type;

	curr_type = token.type;
	//fprintf(stderr, "handle_token with word = %s & type = %d\n", token.word, token.type);
	if (curr_type == WORD)
	{
		if (cmd->prev_type == HEREDOC)
			cmd->here_doc_fd = ft_here_doc(env, ft_strdup(token.word));
		else if (cmd->prev_type == REDIN)
			cmd->infiles[cmd->counters[1]++] = ft_strdup(token.word);
		else if (cmd->prev_type == REDOUT || cmd->prev_type == APPEND)
			cmd->outfiles[cmd->counters[2]++] = ft_strdup(token.word);
		else
			cmd->args[cmd->counters[0]++] = ft_strdup(token.word);
	}
	if (cmd->prev_type == REDOUT)
		cmd->open_options = O_WRONLY | O_CREAT | O_TRUNC;
	if (cmd->prev_type == APPEND)
		cmd->open_options = O_WRONLY | O_CREAT | O_APPEND;
	free(token.word);
	token.word = NULL;
}

int	cmd_creator(t_env *env, t_cmd **cmd, t_token *tokens)
{
	t_cmd	*curr_cmd;
	int		i;

	i = 0;
	if (!tokens || tokens[i].type == END)
		return ((*cmd) = NULL, 0);
	*cmd = init_command(tokens);
	if (!*cmd)
		return (1);
	curr_cmd = *cmd;
	while (tokens[i].type != END)
	{
		if (curr_cmd->prev_type == PIPE)
		{
			curr_cmd->pipe_cmd = init_command(tokens + i);
			if (!curr_cmd->pipe_cmd)
				return (1);
			curr_cmd = curr_cmd->pipe_cmd;
			curr_cmd->prev_type = tokens[i].type;
		}
		handle_token(env, curr_cmd, tokens[i]);
		curr_cmd->prev_type = tokens[i++].type;
	}
	//print_cmd(*cmd);
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
		//fprintf(stderr, "cmd->infiles[0] = %s\ncmd->outfiles[0] = %s\n\
		//cmd->open_options = %i\ncmd->fd_here_doc = %i\ncmd->pipe_cmd = %p\n", \
		//cmd->infiles[0], cmd->outfiles[0], cmd->open_options, cmd->here_doc_fd, \
		//cmd->pipe_cmd);
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
