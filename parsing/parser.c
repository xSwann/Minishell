#include "../parsing.h"
#include <stdio.h>

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
     || chr == '&'
     || chr == '('
     || chr == ')')
        return (1);
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

int    count_token(char *line)
{
	int i;
	int nb_of_token;
	int quote;

	i = 0;
	nb_of_token = 0;
	quote = 0;
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
        if (!is_space(line[i]) && !is_symbol(line[i]) && quote == 0 && line[i] != '\0')
            nb_of_token++;
		if (quote == 0)
		{
			while(line[i] && !is_space(line[i]) && !is_symbol(line[i]) && !is_quote(line[i]))
				i++;
		}
		if(quote != 0)
		{
			while(line[i] && !is_quote(line[i]))
				i++;
		}
    }
/* 	while (line[i])
	{
		while(is_space)
            i++;
		if (quote == 0 && is_quote(line[i])) // si une quote est rencontre, on passe en mode quote
			quote = line[i];
		else if (quote != 0 && line[i] == quote) // si une quote est rencontre et qu'on etait en mode quote, on sort du mode quote
			quote = 0;
		else if (is_space(line[i]) || is_symbol(line[i]) && !quote && line[i] == '\0')
			nb_of_token++;
		i++;
	} */
	return (nb_of_token);
}
