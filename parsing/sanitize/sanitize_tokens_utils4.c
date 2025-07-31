#include "../../includes/parsing.h"
#include "../../includes/built_ins.h"

void	copy_without_quotes(char *old, char *new, size_t len)
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
				new[w++] = old[r++];
		}
		else
			new[w++] = old[r++];
	}
	new[w] = '\0';
}

void	strip_quotes(char **p)
{
	char	*old;
	size_t	len;
	char	*new;

	old = *p;
	len = ft_strlen(old);
	new = malloc(len + 1);
	if (!new)
		return ;
	copy_without_quotes(old, new, len);
	free(old);
	*p = new;
}

void	copy_before_dollar(char **str, char *new, int *i, int *j)
{
	while ((*str)[*i] && (*str)[*i] != '$')
	{
		new[(*j)++] = (*str)[(*i)++];
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

void	copy_expanded_value(char *expanded, char *new, int *j, int *k)
{
	while (expanded[*k])
	{
		new[(*j)++] = expanded[(*k)++];
	}
}
