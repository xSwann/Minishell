/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize_tokens_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slatrech <slatrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:43:41 by slatrech          #+#    #+#             */
/*   Updated: 2025/08/06 14:43:42 by slatrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	replace_expanded_value(char **str, char *expanded, int len)
{
	int		i;
	int		j;
	int		k;
	int		new_len;
	char	*new_str;

	i = 0;
	j = 0;
	k = 0;
	new_len = len + ft_strlen(expanded);
	new_str = malloc(new_len + 1);
	if (!new_str)
		return ;
	copy_before_dollar(str, new_str, &i, &j);
	skip_variable_name(str, &i);
	copy_expanded_value(expanded, new_str, &j, &k);
	while ((*str)[i])
		new_str[j++] = (*str)[i++];
	new_str[j] = '\0';
	free(*str);
	*str = new_str;
}

void	copy_before_dollar_erase(char **str, char *new_str, int *i, int *j)
{
	while ((*str)[*i] && (*str)[*i] != '$')
	{
		new_str[(*j)++] = (*str)[(*i)++];
	}
}

void	skip_variable_erase(char **str, int *i)
{
	(*i)++;
	if (ft_isdigit((*str)[*i]))
		*i = 2;
	else
	{
		while ((*str)[*i] && ft_isalnum((*str)[*i]))
			(*i)++;
	}
}

void	erase_expand(char **str, int len)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_str = malloc(len + 1);
	if (!new_str)
		return ;
	copy_before_dollar_erase(str, new_str, &i, &j);
	skip_variable_erase(str, &i);
	while ((*str)[i])
		new_str[j++] = (*str)[i++];
	new_str[j] = '\0';
	free(*str);
	*str = new_str;
}

void	skip_leading_spaces(char *str, int *i)
{
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
}
