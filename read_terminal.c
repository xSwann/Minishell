#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "parsing/parsing.h"
#include "exec/exec.h"

int	read_terminal(char **envp)
{
	char	*line;
	int		nb_of_token;
	char	**tokens;
	t_token	*tokens_struct;
	t_cmd	*cmd;

	while (1)
	{
		line = readline("Minishell: ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		nb_of_token = count_tokens(line);
		tokens = ft_calloc(nb_of_token + 1, sizeof(char *));
		if (!tokens)
			exit(EXIT_FAILURE);
		//fprintf(stderr, "Nb of tokens: %d\n", nb_of_token);
		put_tokens_in_tab(nb_of_token, line, tokens);
		tokens_struct = malloc(sizeof(t_token) * (nb_of_token + 1));
		if (!tokens_struct)
			exit(EXIT_FAILURE);
		tokens_struct = (t_token *)ft_memset(tokens_struct, 0, \
			sizeof(t_token) * (nb_of_token + 1));
		put_tokens_in_struct(tokens, nb_of_token, tokens_struct);
		print_tokens(nb_of_token, tokens_struct);
		cmd = NULL;
		if (cmd_creator(&cmd, tokens_struct))
			exit(EXIT_FAILURE);
		//print_cmd(cmd);
		cmd_executor(envp, &cmd);
		free(tokens_struct);
		if (line)
			free(line);
		line = NULL;
		tokens = NULL;
	}
	if (line)
		free(line);	
	return (rl_clear_history(), 0);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	read_terminal(envp);
	return (0);
}
