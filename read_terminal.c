#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "parsing.h"

int    read_terminal()
{
    char    *line;
    int     nb_of_token;
    while (1)
    {
        line = readline("Minishell: ");
        nb_of_token = count_token(line);
        printf("Nb of tokens: %d\n", nb_of_token);
        printf("%s\n", line);
        free(line);
    }
    return (0);
}

int main()
{
    read_terminal();
    return (0);
}