#ifndef PARSING_H
# define PARSING_H

typedef enum type
{
    INVALID = 0,
    WORD,
    PIPE,
    REDIN,
    HEREDOC,
    REDOUT,
    APPEND,
    END
}           t_type;

typedef struct s_token
{
    char    *word;
    t_type     type;
}   t_token;

// FUNC
int    count_token(char *line);

# endif