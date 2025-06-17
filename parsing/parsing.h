#ifndef PARSING_H
# define PARSING_H

/*
** Includes
*/
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include "../libft/libft.h"

/*
** Token types
*/
typedef enum e_type
{
	INVALID = 0,
	WORD,
	PIPE,
	REDIN,
	HEREDOC,
	REDOUT,
	APPEND,
	END
}	t_type;

/*
** Token structure
*/
typedef struct s_token
{
	char	*word;
	t_type	type;
}	t_token;

/*
** Tokenization functions
*/
int		count_tokens(char *line);
void	put_tokens_in_tab(int nb_of_token, char *line, char **tab);
void	put_tokens_in_struct(char **tab, int nb_of_tokens);

/*
** Utility functions
*/
int		is_space(char chr);
int		is_symbol(char chr);
int		is_double_symbol(char *str, int i);
int		is_quote(char chr);
void	fill_line(char *tab, char *line, int start, int end);
void	symbol_handler(int *i, char *line);

#endif /* PARSING_H */
