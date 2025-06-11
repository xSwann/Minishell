#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "parsing/parsing.h"

int    read_terminal()
{
    char    *line;
    int     nb_of_token;
    char    **tokens;
    int i;

    i = 0;
    while (1)
    {
        line = readline("Minishell: ");
        nb_of_token = count_tokens(line);
        tokens = malloc(sizeof(t_token) * nb_of_token + 1);
        if (!tokens)
            exit(EXIT_FAILURE);
        tokens[nb_of_token] = 0;
        printf("Nb of tokens: %d\n", nb_of_token);
        put_tokens_in_tab(nb_of_token, line, tokens);
        while (tokens[i])
        {
		    printf("line: %s\n", tokens[i]);
		    i++;
	    }
        free(line);
    }
    return (0);
}

int main()
{
    read_terminal();
    return (0);
}