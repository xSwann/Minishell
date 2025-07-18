#include "../includes/parsing.h"

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

void	symbol_handler(int *i, char *line)
{
	if (is_double_symbol(line, *i))
		*i += 2;
	else
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

void put_tokens_in_tab(int nb_of_token, char *line, t_tab *tab)
{
    int i = 0, j = 0;
    int start, len;

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

        if ((tab[j].str[0] == '\'' && tab[j].str[len - 1] == '\'') ||
            (tab[j].str[0] == '"'  && tab[j].str[len - 1] == '"'))
            tab[j].quoted = 1;
		else if ((tab[j].str[0] == '\'' && tab[j].str[len - 1] == '\'') ||
            (tab[j].str[0] == 39  && tab[j].str[len - 1] == 39))
            tab[j].quoted = 2;
        else
            tab[j].quoted = 0;
        j++;
    }
}
