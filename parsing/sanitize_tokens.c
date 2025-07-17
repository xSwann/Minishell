#include "../includes/parsing.h"
#include "../includes/built_ins.h"

static void	strip_quotes(char **p)
{
	char	*old;
	char	*new;
	char	q;
	size_t	r;
	size_t	w;

	old = *p;
	new = malloc(ft_strlen(old) + 1);
	if (!new)
		return ;
	q = '\0';
	r = 0;
	w = 0;
	while (old[r])
	{
		if ((old[r] == '"' || old[r] == '\''))
		{
			if (!q)
			{
				q = old[r];
				r++;
			}
			else if (old[r] == q)
			{
				q = '\0';
				r++;
			}
			else
			{
				new[w++] = old[r++];
			}
		}
		else
		{
			new[w++] = old[r++];
		}
	}
	new[w] = '\0';
	free(old);
	*p = new;
}

void	replace_expanded_value(char **str, char *expanded, int len)
{
	int		i;
	int		j;
	int		k;
	char	*new;

	i = 0;
	j = 0;
	k = 0;
	new = malloc(len + ft_strlen(expanded) + 1);
	if (!new)
		return ;
	while ((*str)[i] && (*str)[i] != '$')
		new[j++] = (*str)[i++];
	i++;
	if ((*str)[i] != '?')
	{
		while ((*str)[i] && ft_isalnum((*str)[i]))
			i++;
	}
	else
	{
		i++;
	}
	while (expanded[k])
		new[j++] = expanded[k++];
	while ((*str)[i])
		new[j++] = (*str)[i++];
	new[j] = '\0';
	free(*str);
	*str = new;
}

void	erase_expand(char **str, int len)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = malloc(len + 1);
	if (!new)
		return ;
	while ((*str)[i] && (*str)[i] != '$')
		new[j++] = (*str)[i++];
	i++;
	if (ft_isdigit((*str)[i]))
		i = 2;
	else
	{
		while ((*str)[i] && ft_isalnum((*str)[i]))
			i++;
	}
	while ((*str)[i])
		new[j++] = (*str)[i++];
	new[j] = '\0';
	free(*str);
	*str = new;
}

void	expand_var(char **str, t_env *env)
{
	int		i;
	int		start;
	int		len;
	char	*to_expand;
	char	*expanded;

	i = 0;
	start = 0;
	len = 0;
	to_expand = NULL;
	while ((*str)[i] && (*str)[i] != '$')
		i++;
	start = i++;
	while ((*str)[i] && ft_isalnum((*str)[i]))
		i++;
	if ((*str)[start + 1] == '?')
	{
		to_expand = ft_strdup("EXIT_CODE");
		len = 1;
	}
	else if (ft_isdigit((*str)[start + 1]) || is_quote((*str)[start + 1]))
	{
		to_expand = ft_strdup("9");
		len = 1;
	}
	else
	{
		to_expand = ft_substr(*str, start + 1, i - (start + 1));
		len = ft_strlen(to_expand);
	}
	expanded = get_env(env, to_expand);
	free(to_expand);
	if (!expanded)
		erase_expand(str, ft_strlen(*str) - len);
	else
		replace_expanded_value(str, expanded, ft_strlen(*str) - len);
}

void	sanitize_tokens(char **tokens, t_env *env)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	while (tokens[i])
	{
		j = 0;
		quote = '\0';
		while (tokens[i][j])
		{
			if (tokens[i][j] == '$')
			{
				if (tokens[i][j + 1]
				&& ((ft_isalnum(tokens[i][j + 1]) || tokens[i][j + 1] == '?'|| (is_quote(tokens[i][j+1]) && quote == '\0')))
				&& (((quote == '\0' || quote == '"'))))
				{
					expand_var(&tokens[i], env);
					continue ;
				}
			}
			else if (quote == '\0' && is_quote(tokens[i][j]))
			{
				quote = tokens[i][j];
				j++;
				continue ;
			}
			else if (quote != '\0' && tokens[i][j] == quote)
			{
				quote = '\0';
				j++;
				continue ;
			}
			j++;
		}
		strip_quotes(&tokens[i]);
		i++;
	}
}
