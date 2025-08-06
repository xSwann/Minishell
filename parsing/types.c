/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slatrech <slatrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:43:37 by slatrech          #+#    #+#             */
/*   Updated: 2025/08/06 14:43:38 by slatrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"
#include "../includes/built_ins.h"

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
	else if (token.word[0] == '<'
		&& token.word[1] == '<' && ft_strlen(token.word) == 2)
		return (HEREDOC);
	else if (token.word[0] == '>'
		&& token.word[1] == '>' && ft_strlen(token.word) == 2)
		return (APPEND);
	else if (token.word[0] == '<'
		&& ft_strlen(token.word) == 1)
		return (REDIN);
	else if (token.word[0] == '>'
		&& ft_strlen(token.word) == 1)
		return (REDOUT);
	return (WORD);
}

int	error_parser_printer(t_env **env, char *word)
{
	write(2, "minishell: syntax error near unexpected token `", 47);
	if (word && *word)
		write(2, word, ft_strlen(word));
	else
		write(2, "newline", 7);
	write(2, "'\n", 2);
	ft_export(env, "EXIT_CODE=2");
	return (2);
}

int	validate_tokens(t_env **env, t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens && tokens[i].type && tokens[i].type != END)
	{
		if (tokens[i].type == PIPE)
		{
			if (i == 0 || tokens[i + 1].type == END
				|| tokens[i + 1].type == PIPE)
				return (error_parser_printer(env, tokens[i].word));
		}
		else if (tokens[i].type == REDIN || tokens[i].type == REDOUT
			|| tokens[i].type == APPEND || tokens[i].type == HEREDOC)
		{
			if (tokens[i + 1].type == END)
				return (error_parser_printer(env, tokens[i + 1].word));
			if (tokens[i + 1].type != WORD)
				return (error_parser_printer(env, tokens[i + 1].word));
		}
		i++;
	}
	return (0);
}

int	tks_to_struct(t_env **env, t_tab *tab, int nb_of_tks, t_token **tks)
{
	int	i;

	i = 0;
	while (i < nb_of_tks)
	{
		(*tks)[i].word = strdup(tab[i].str);
		free(tab[i].str);
		if (tab[i].quoted == 0)
			(*tks)[i].type = find_type((*tks)[i]);
		else
			(*tks)[i].type = WORD;
		i++;
	}
	free(tab);
	(*tks)[i].word = NULL;
	(*tks)[i].type = find_type((*tks)[i]);
	if (validate_tokens(env, *tks))
	{
		while (--i >= 0)
			free((*tks)[i].word);
		free(*tks);
		return (*tks = NULL, 1);
	}
	return (0);
}
