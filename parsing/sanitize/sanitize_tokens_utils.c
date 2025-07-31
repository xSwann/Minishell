#include "../../includes/parsing.h"
#include "../../includes/built_ins.h"

void	replace_expanded_value(char **str, char *expanded, int len)
{
	int		i;
	int		j;
	int		k;
	int		newlen;
	char	*new;

	i = 0;
	j = 0;
	k = 0;
	newlen = len + ft_strlen(expanded);
	new = malloc(newlen + 1);
	if (!new)
		return ;
	copy_before_dollar(str, new, &i, &j);
	skip_variable_name(str, &i);
	copy_expanded_value(expanded, new, &j, &k);
	while ((*str)[i])
		new[j++] = (*str)[i++];
	new[j] = '\0';
	free(*str);
	*str = new;
}

void	copy_before_dollar_erase(char **str, char *new, int *i, int *j)
{
	while ((*str)[*i] && (*str)[*i] != '$')
	{
		new[(*j)++] = (*str)[(*i)++];
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
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc(len + 1);
	if (!new)
		return ;
	copy_before_dollar_erase(str, new, &i, &j);
	skip_variable_erase(str, &i);
	while ((*str)[i])
		new[j++] = (*str)[i++];
	new[j] = '\0';
	free(*str);
	*str = new;
}

void	skip_leading_spaces(char *str, int *i)
{
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
}
