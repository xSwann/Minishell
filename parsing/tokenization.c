/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slatrech <slatrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:43:28 by slatrech          #+#    #+#             */
/*   Updated: 2025/08/06 14:43:29 by slatrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int	is_space(char chr)
{
	if (chr == 32 || chr == 4 || chr == 9)
		return (1);
	return (0);
}

int	is_symbol(char chr)
{
	if (chr == '>'
		|| chr == '<'
		|| chr == '|'
		|| chr == '&')
		return (1);
	return (0);
}

int	is_double_symbol(char *str, int i)
{
	if (str[i] == '>')
	{
		if (str[i + 1] == '>')
			return (1);
	}
	if (str[i] == '<')
	{
		if (str[i + 1] == '<')
			return (1);
	}
	return (0);
}

int	is_quote(char chr)
{
	if (chr == 39)
		return (1);
	if (chr == 34)
		return (1);
	return (0);
}

void	fill_line(char *tab, char *line, int start, int end)
{
	int	i;

	i = 0;
	while (start < end)
	{
		tab[i] = line[start];
		i++;
		start++;
	}
	tab[i] = '\0';
}
