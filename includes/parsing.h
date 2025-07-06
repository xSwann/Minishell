#ifndef PARSING_H
# define PARSING_H

/*==============================
=          INCLUDES            =
==============================*/

# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <stdbool.h>
# include "structs.h"
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h> // pour O_CREAT, O_TRUNC, O_WRONLY, etc.
# include <errno.h>
# include "libft.h"

/*==============================
=     TOKENIZATION FUNCTIONS   =
==============================*/

int		count_tokens(char *line);
void	put_tokens_in_tab(int nb_of_token, char *line, char **tab);
void	put_tokens_in_struct(char **tab, int nb_of_tokens, t_token *tokens);
void	print_tokens(int nb_of_tokens, t_token *tokens);

/*==============================
=       UTILITY FUNCTIONS      =
==============================*/

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

#endif
