#include <stdlib.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "parsing/parsing.h"

int    read_terminal()
{
    char    *line;
    int     nb_of_token;
    char    **tokens;
    int		i;
    t_token	*tokens_struct;


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
       	tokens_struct = malloc(sizeof(t_token) * (nb_of_token + 1));
        put_tokens_in_struct(tokens, nb_of_token, tokens_struct);
        print_tokens(nb_of_token, tokens_struct);
        free(line);
    }
    return (0);
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    (void)envp;
    read_terminal();
    return (0);
}
