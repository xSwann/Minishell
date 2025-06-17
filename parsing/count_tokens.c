#include "parsing.h"

static void	skip_spaces(char *line, int *i)
{
	while (line[*i] && is_space(line[*i]))
		(*i)++;
}

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
	{
		symbol_handler(i, line);
	}
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

int	count_tokens(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		skip_spaces(line, &i);
		if (!line[i])
			break ;
		count++;
		skip_token(line, &i);
	}
	return (count);
}
