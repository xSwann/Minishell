#include <stdlib.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "parsing/parsing.h"

int    read_terminal()
{
	t_token	**tokens_struct;
	t_cmd	*cmd;
    char    *line;
    int     nb_of_token;
    char    **tokens;
    int		i;

    i = 0;
    while (1)
    {
        line = readline("Minishell: ");
        nb_of_token = count_tokens(line);
        tokens = malloc(sizeof(t_token *) * (nb_of_token + 1));
		tokens = (char **)ft_memset(tokens, 0, sizeof(t_token *) * (nb_of_token + 1));
        if (!tokens)
            exit(EXIT_FAILURE);
        printf("Nb of tokens: %d\n", nb_of_token);
        put_tokens_in_tab(nb_of_token, line, tokens);
		/*while (tokens[i])
        {
		    printf("tokens: %s\n", tokens[i]);
		    i++;
	    } */
        tokens_struct = put_tokens_in_struct(tokens, nb_of_token);
		cmd = cmd_creator(tokens_struct);
		print_cmd(cmd);
		free(tokens_struct[0]);
		free(tokens_struct);
		/*cmd_executor(cmd);
		while (cmd && cmd->pipe_cmd)
		{
			prev_cmd = cmd;
			cmd = cmd->pipe_cmd;
			free(prev_cmd);
		}*/
        free(line);
    }
    return (0);
}

int main()
{
    read_terminal();
    return (0);
}
