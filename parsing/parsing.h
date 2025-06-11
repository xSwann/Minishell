#ifndef PARSING_H
# define PARSING_H

typedef enum type
{
    INVALID = 0,
    WORD,           //le reste
    PIPE,           // |
    REDIN,          // >
    HEREDOC,        // <<
    REDOUT,         // >
    APPEND,         // >>
    END
}           t_type;

/* << HEREDOC
< redin 
> redout 
>> append
'\0' END */

typedef struct s_token
{
    char    *word;
    t_type     type;
}   t_token;

// FUNC
int    count_tokens(char *line);
void	put_tokens_in_tab(int nb_of_token, char *line, char **tab);

# endif