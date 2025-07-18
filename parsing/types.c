#include "../includes/parsing.h"

void	print_tokens(int nb_of_tokens, t_token *tokens)
{
	int	i;

	i = 0;
	while (i <= nb_of_tokens)
	{
		printf("word = %s ", tokens[i].word);
		if (tokens[i].type == PIPE)
			printf("type = PIPE\n");
		else if (tokens[i].type == REDIN)
			printf("type = REDIN\n");
		else if (tokens[i].type == HEREDOC)
			printf("type = HEREDOC\n");
		else if (tokens[i].type == REDOUT)
			printf("type = REDOUT\n");
		else if (tokens[i].type == APPEND)
			printf("type = APPEND\n");
		else if (tokens[i].type == WORD)
			printf("type = WORD\n");
		else if (tokens[i].type == END)
			printf("type = END\n");
		i++;
	}
}

t_type	find_type(t_token token)
{
	if (!token.word)
		return (END);
	if (token.word[0] == '|')
		return (PIPE);
	else if (token.word[0] == '<' && token.word[1] == '<' && ft_strlen(token.word) == 2)
		return (HEREDOC);
	else if (token.word[0] == '>' && token.word[1] == '>' && ft_strlen(token.word) == 2)
		return (APPEND);
	else if (token.word[0] == '<' && ft_strlen(token.word) == 1)
		return (REDIN);
	else if (token.word[0] == '>' && ft_strlen(token.word) == 1)
		return (REDOUT);
	return (WORD);
}

void	put_tokens_in_struct(t_tab *tab, int nb_of_tokens, t_token *tokens)
{
	int	i;

	i = 0;
	while (i < nb_of_tokens)
	{
		tokens[i].word = strdup(tab[i].str);
		if(tab[i].quoted == 0)
			tokens[i].type = find_type(tokens[i]);
		else
			tokens[i].type = WORD;
		i++;
	}
	tokens[i].word = NULL;
	tokens[i].type = find_type(tokens[i]);
}
