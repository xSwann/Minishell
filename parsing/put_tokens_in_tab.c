/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_tokens_in_tab.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slatrech <slatrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:43:26 by slatrech          #+#    #+#             */
/*   Updated: 2025/08/06 14:43:27 by slatrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static void	skip_quoted_segment(char *line, int *i)
{
	char	qc;

	qc = line[*i];
	(*i)++;
	while (line[*i] && line[*i] != qc)
		(*i)++;
	if (line[*i] == qc)
		(*i)++;
}

static void	skip_spaces(char *line, int *i)
{
	while (line[*i] && is_space(line[*i]))
		(*i)++;
}

static void	skip_token(char *line, int *i)
{
	if (is_quote(line[*i]))
	{
		skip_quoted_segment(line, i);
		while (line[*i] && !is_space(line[*i]) && !is_symbol(line[*i]))
		{
			if (is_quote(line[*i]))
				skip_quoted_segment(line, i);
			else
				(*i)++;
		}
	}
	else if (is_symbol(line[*i]))
		symbol_handler(i, line);
	else
	{
		while (line[*i] && !is_space(line[*i]) && !is_symbol(line[*i]))
		{
			if (is_quote(line[*i]))
				skip_quoted_segment(line, i);
			else
				(*i)++;
		}
	}
}

void	search_quote(t_tab **tab, int j, int len)
{
	if (((*tab)[j].str[0] == '\'' && (*tab)[j].str[len - 1] == '\'')
		|| ((*tab)[j].str[0] == '"' && (*tab)[j].str[len - 1] == '"'))
		(*tab)[j].quoted = 1;
	else if (((*tab)[j].str[0] == '\'' && (*tab)[j].str[len - 1] == '\'')
		|| ((*tab)[j].str[0] == 39 && (*tab)[j].str[len - 1] == 39))
		(*tab)[j].quoted = 2;
	else
		(*tab)[j].quoted = 0;
}

void	put_tokens_in_tab(int nb_of_token, char *line, t_tab *tab)
{
	int	i;
	int	j;
	int	start;
	int	len;

	i = 0;
	j = 0;
	while (line[i] && j < nb_of_token)
	{
		skip_spaces(line, &i);
		if (!line[i])
			break ;
		start = i;
		skip_token(line, &i);
		len = i - start;
		tab[j].str = malloc(len + 1);
		if (!tab[j].str)
			exit(EXIT_FAILURE);
		fill_line(tab[j].str, line, start, i);
		search_quote(&tab, j, len);
		j++;
	}
	free(line);
	line = NULL;
}
