#include "../../includes/parsing.h"

void	copy_without_quotes(char *old, char *new_str, size_t len)
{
	char	q;
	size_t	r;
	size_t	w;

	q = '\0';
	r = 0;
	w = 0;
	while (r < len)
	{
		if (old[r] == '"' || old[r] == '\'')
		{
			if (q == '\0')
				q = old[r++];
			else if (old[r] == q)
			{
				q = '\0';
				r++;
			}
			else
				new_str[w++] = old[r++];
		}
		else
			new_str[w++] = old[r++];
	}
	new_str[w] = '\0';
}

void	strip_quotes(char **p)
{
	char	*old;
	size_t	len;
	char	*new_str;

	old = *p;
	len = ft_strlen(old);
	new_str = malloc(len + 1);
	if (!new_str)
		return ;
	copy_without_quotes(old, new_str, len);
	free(old);
	*p = new_str;
}

void	copy_before_dollar(char **str, char *new_str, int *i, int *j)
{
	while ((*str)[*i] && (*str)[*i] != '$')
	{
		new_str[(*j)++] = (*str)[(*i)++];
	}
}

void	skip_variable_name(char **str, int *i)
{
	(*i)++;
	if ((*str)[*i] == '?')
		(*i)++;
	else
	{
		while ((*str)[*i] && ft_isalnum((*str)[*i]))
			(*i)++;
	}
}

void	copy_expanded_value(char *expanded, char *new_str, int *j, int *k)
{
	while (expanded[*k])
	{
		new_str[(*j)++] = expanded[(*k)++];
	}
}
