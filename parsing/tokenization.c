#include "parsing.h"

int is_space(char chr)
{
    if (chr == 32 || chr == 4)
        return (1);
    return (0);
}

int is_symbol(char chr)
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
		if (str[i+1] == '>')
			return (1);
	}
	if (str[i] == '<')
	{
		if (str[i+1] == '<')
			return (1);
	}
	return (0);
}

int is_quote(char chr)
{
    if (chr == 39)
        return (1);
    if (chr == 34)
        return (1);
    return (0);
}

void	fill_line(char *tab, char *line, int start, int end)
{
	int i;
    i = 0;

    while (start < end)
    {
        tab[i] = line[start];
        i++;
        start++;
    }
    tab[i] = '\0';
}

int    count_tokens(char *line)
{
	int i;
	int nb_of_token;
	int quote;
	int symbol;
	int	old_symbol;

	i = 0;
	nb_of_token = 0;
	quote = 0;
	symbol = 0;
	old_symbol = 0;
	while (line[i])
    {
		if (quote == 0 && is_quote(line[i])) // si une quote est rencontre, on passe en mode quote
		{
			quote = line[i];
			i++;
		}
		else if (line[i] == quote) // si une quote est rencontre et qu'on etait en mode quote, on sort du mode quote
		{
			quote = 0;
			i++;
		}
        while(line[i] && is_space(line[i]))
            i++;
		if (line[i] && is_symbol(line[i]))
		{
			if(line[i] && is_double_symbol(line, i))
				i += 2;
			else 
				i++;
			nb_of_token++;
		}
		if (!is_space(line[i]) && !is_symbol(line[i]) && quote == 0 && line[i] != '\0')
		{
            nb_of_token++;
		}
		if (quote == 0)
		{
			while (line[i] && !is_space(line[i]) && !is_symbol(line[i]) && !is_quote(line[i]))
				i++;
		}
		if (quote != 0)
		{
			while (line[i] && line[i] != quote)
				i++;
		}
    }
	if (quote != 0)// Erreur si l'utilisateur a laisse une quote ouverte (a transferer vers gestionnaire d'erreur)
		printf("Error: quote no-closed\n");
	return (nb_of_token);
}

void	put_tokens_in_tab(int nb_of_token, char *line, char **tab)
{
	int i;
	int l;
	int j;
	int k;
	int end_quote;
	int quote;
	int symbol;
	int old_symbol;
	int quote_position;

	i = 0;
	l = 0;
	j = 0;
	k = 0;
	quote_position = 0;;
	symbol = 0;
	old_symbol = 0;
	end_quote = 0;
	quote = 0;
	while (line[i])
    {
		if (quote == 0 && is_quote(line[i])) // si une quote est rencontre, on passe en mode quote
		{
			quote_position = i;
			quote = line[i];
			end_quote = 1;
			i++;
		}
		else if (line[i] == quote) // si une quote est rencontre et qu'on etait en mode quote, on sort du mode quote
		{
			quote = 0;
			end_quote = 0;
			i++;
		}
        while(line[i] && is_space(line[i]))
            i++;
		if(quote != 0)
			l = quote_position;
		else
			l = i;
		if (quote == 0)
		{
			while(line[i] && !is_space(line[i]) && !is_symbol(line[i]) && !is_quote(line[i]))
				i++;
		}
		if(quote != 0)
		{
			while(line[i] && line[i] != quote)
				i++;
		}
		if (is_symbol(line[i]))
		{

			if (i != 0)
			{
				if (!is_space(line[i-1]) && !is_symbol(line[i-1]))
				{
					tab[j] = malloc(sizeof(char) * (i + end_quote - l) + 1);
					if (!tab[j])
						exit(EXIT_FAILURE);
					fill_line(tab[j], line, l, i + end_quote);
					j++;
				}
			}
			if (line[i] == '<' || line[i] == '>')
			{
				if (line[i+1] == line[i])
				{
					tab[j] = malloc(sizeof(char) * (2) + 1);
					fill_line(tab[j], line, i, i+2);
					i++;
				}
				else if (line[i+1] != line[i])
				{
					tab[j] = malloc(sizeof(char) * (1) + 1);
					fill_line(tab[j], line, i, i+1);
				}
				i++;
				j++;
			}
			else
			{
				tab[j] = malloc(sizeof(char) * (2) + 1);
				fill_line(tab[j], line, i, i+1);
				i++;
				j++;
			}
		}
		else if (i - l != 0)
		{
			tab[j] = malloc(sizeof(char) * (i + end_quote - l) + 1);
			if (!tab[j])
				exit(EXIT_FAILURE);
			fill_line(tab[j], line, l, i + end_quote);
			j++;
		}
    }
	if(quote != 0)// Erreur si l'utilisateur a laisse une quote ouverte (a transferer vers gestionnaire d'erreur)
		printf("Error: quote no-closed\n");
	i = 0;
	j = 0;
/* 	while (tab[i])
	{
		printf("line: %s\n", tab[i]);
		i++;
	} */
}
