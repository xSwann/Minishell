/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize_tokens_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slatrech <slatrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:43:43 by slatrech          #+#    #+#             */
/*   Updated: 2025/08/06 14:43:44 by slatrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	copy_word_characters(char *str, int *i, int *j, int *in_word)
{
	while (str[*i] && str[*i] != ' ' && str[*i] != '\t')
	{
		str[(*j)++] = str[(*i)++];
		*in_word = 1;
	}
}

void	handle_spaces(char *str, int *i, int *j, int *in_word)
{
	if (*in_word)
	{
		str[(*j)++] = ' ';
		*in_word = 0;
	}
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
}

void	clear_space(char *str)
{
	int	i;
	int	j;
	int	in_word;

	i = 0;
	j = 0;
	in_word = 0;
	skip_leading_spaces(str, &i);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			copy_word_characters(str, &i, &j, &in_word);
		else
			handle_spaces(str, &i, &j, &in_word);
	}
	if (j > 0 && str[j - 1] == ' ')
		j--;
	str[j] = '\0';
}

void	find_dollar_position(char **str, int *i)
{
	while ((*str)[*i] && (*str)[*i] != '$')
		(*i)++;
}

void	find_variable_end(char **str, int *i)
{
	while ((*str)[*i] && (ft_isalnum((*str)[*i])))
		(*i)++;
}
