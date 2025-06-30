#ifndef PARSING_H
# define PARSING_H

/*
** Includes
*/
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h> // pour O_CREAT, O_TRUNC, O_WRONLY, etc.
# include <string.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <errno.h>
# include <readline/history.h>
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
** Command structure
*/
typedef struct s_cmd	t_cmd;

struct	s_cmd
{
	char	**args;
	char	*outfile;
	char	*infile;
	int		here_doc_fd;
	int		open_options;
	t_cmd	*pipe_cmd;
};

/*==============================
=       TOKEN STRUCTURE        =
==============================*/

typedef struct s_token
{
	char	*word;
	t_type	type;
}	t_token;

/*==============================
=     TOKENIZATION FUNCTIONS   =
==============================*/

int		count_tokens(char *line);
void	put_tokens_in_tab(int nb_of_token, char *line, char **tab);
void	put_tokens_in_struct(char **tab, int nb_of_tokens, t_token *tokens);
void	print_tokens(int nb_of_tokens, t_token *tokens);

/*
** Utility functions
*/
int		is_space(char chr);
int		is_symbol(char chr);
int		is_double_symbol(char *str, int i);
int		is_quote(char chr);
void	fill_line(char *tab, char *line, int start, int end);
void	symbol_handler(int *i, char *line);

/*==============================
=      COMMAND_FUNCTIONS      =
==============================*/

int		cmd_creator(t_cmd **cmd, t_token *tokens);
void	print_cmd(t_cmd *cmd);

/*==============================
=    HERE_DOC MANIPULATIONS    =
==============================*/

int		ft_here_doc(char *limiter);

#endif /* PARSING_H */
