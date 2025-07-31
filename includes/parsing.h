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
void	symbol_handler(int *i, char *line);

void	put_tokens_in_tab(int nb_of_token, char *line, t_tab *tab);
int     put_tks_in_struct(t_env **env, t_tab *tab, int nb_of_tks, t_token **tks);


void	print_tokens(int nb_of_tokens, t_token *tokens);


//sanitize_tokens
void	sanitize_tokens(t_tab *tokens, t_env *env);

//sanitize_tokens_utils1
void	replace_expanded_value(char **str, char *expanded, int len);
void	copy_before_dollar_erase(char **str, char *new, int *i, int *j);
void	skip_variable_erase(char **str, int *i);
void	erase_expand(char **str, int len);
void	skip_leading_spaces(char *str, int *i);

//sanitize_tokens_utils2
void	copy_word_characters(char *str, int *i, int *j, int *in_word);
void	handle_spaces(char *str, int *i, int *j, int *in_word);
void	clear_space(char *str);
void	find_dollar_position(char **str, int *i);
void	find_variable_end(char **str, int *i);

//sanitize_tokens_utils3
void	handle_special_cases(char **str, char **to_expand, int start);
void	set_to_expand(char **to_expand, char **str);
void	expand_var(char **str, t_env *env);
int     should_expand(t_tab *tokens, int i, int j, char quote);
void	handle_expansion(t_tab *tokens, t_env *env, int i, char quote);

//sanitize_tokens_utils4
void	copy_without_quotes(char *old, char *new, size_t len);
void	strip_quotes(char **p);
void	copy_before_dollar(char **str, char *new, int *i, int *j);
void	skip_variable_name(char **str, int *i);
void	copy_expanded_value(char *expanded, char *new, int *j, int *k);



/*==============================
=       UTILITY FUNCTIONS      =
==============================*/

int		is_space(char chr);
int		is_quote(char chr);
int		is_symbol(char chr);
int		is_double_symbol(char *str, int i);
void	symbol_handler(int *i, char *line);
void	expand_var(char **str, t_env *env);
int		error_printer(char *str, char *str2);
void	fill_line(char *tab, char *line, int start, int end);

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
