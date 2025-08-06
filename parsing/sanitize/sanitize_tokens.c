/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slatrech <slatrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:43:39 by slatrech          #+#    #+#             */
/*   Updated: 2025/08/06 14:43:40 by slatrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	handle_quote_start(t_tab *tokens, int i, int *j, char *quote)
{
	*quote = tokens[i].str[(*j)++];
}

void	handle_quote_end(int *j, char *quote)
{
	*quote = '\0';
	(*j)++;
}

void	process_token_char(t_token_data *data)
{
	if (should_expand(data->tokens, data->i, *(data->j), *(data->quote)))
	{
		handle_expansion(data->tokens, data->env, data->i, *(data->quote));
		*(data->j) = 0;
		return ;
	}
	if (*(data->quote) == '\0'
		&& is_quote(data->tokens[data->i].str[*(data->j)]))
		handle_quote_start(data->tokens, data->i, data->j, data->quote);
	else if (*(data->quote) != '\0'
		&& data->tokens[data->i].str[*(data->j)] == *(data->quote))
		handle_quote_end(data->j, data->quote);
	else
		(*(data->j))++;
}

void	sanitize_single_token(t_tab *tokens, t_env *env, int i)
{
	int				j;
	char			quote;
	t_token_data	data;

	j = 0;
	quote = '\0';
	data.tokens = tokens;
	data.env = env;
	data.i = i;
	data.j = &j;
	data.quote = &quote;
	while (tokens[i].str[j])
		process_token_char(&data);
	strip_quotes(&tokens[i].str);
}

void	sanitize_tokens(t_tab *tokens, t_env *env)
{
	int	i;

	i = 0;
	while (tokens[i].str)
	{
		sanitize_single_token(tokens, env, i);
		i++;
	}
}
