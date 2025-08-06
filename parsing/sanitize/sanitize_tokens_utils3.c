/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize_tokens_utils3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slatrech <slatrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:43:45 by slatrech          #+#    #+#             */
/*   Updated: 2025/08/06 14:43:46 by slatrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/built_ins.h"

void	handle_special_cases(char **str, char **to_expand, int start)
{
	if ((*str)[start + 1] == '?')
		*to_expand = ft_strdup("EXIT_CODE");
	else if (ft_isdigit((*str)[start + 1]) || is_quote((*str)[start + 1]))
		*to_expand = ft_strdup("9");
}

void	set_to_expand(char **to_expand, char **str)
{
	int	i;
	int	start;

	i = 0;
	find_dollar_position(str, &i);
	start = i++;
	find_variable_end(str, &i);
	if ((*str)[start + 1] == '?' || ft_isdigit((*str)[start + 1])
		|| is_quote((*str)[start + 1]))
		handle_special_cases(str, to_expand, start);
	else
		*to_expand = ft_substr(*str, start + 1, i - (start + 1));
}

void	expand_var(char **str, t_env *env)
{
	int		len;
	char	*expanded;
	char	*to_expand;

	len = 0;
	set_to_expand(&to_expand, str);
	expanded = get_env(env, to_expand);
	free(to_expand);
	if (!expanded)
		erase_expand(str, ft_strlen(*str) - len);
	else
		replace_expanded_value(str, expanded, ft_strlen(*str) - len);
	free(expanded);
}

int	should_expand(t_tab *tokens, int i, int j, char quote)
{
	return (tokens[i].str[j] == '$'
		&& (quote == '\0' || quote == '"')
		&& tokens[i].str[j + 1]
		&& (ft_isalnum(tokens[i].str[j + 1])
			|| tokens[i].str[j + 1] == '?'
			|| (is_quote(tokens[i].str[j + 1]) && quote == '\0')));
}

void	handle_expansion(t_tab *tokens, t_env *env, int i, char quote)
{
	expand_var(&tokens[i].str, env);
	if (quote == '\0')
		clear_space(tokens[i].str);
}
