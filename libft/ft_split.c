#include "../includes/libft.h"

static size_t	ft_countwords(const char *str, int c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i - 1] == c || i == 0) && str[i] != c)
			j++;
		i++;
	}
	return (j);
}

static size_t	ft_wordlen(const char *str, int c, size_t k)
{
	size_t	j;

	j = 0;
	while (str[k] && str[k] == c)
		k++;
	while (str[k + j] != c && str[k + j])
		j++;
	return (j);
}

static void	ft_free_table(char **table)
{
	size_t	i;

	i = 0;
	while (table[i])
	{
		free(table[i]);
		i++;
	}
	free(table);
}

static char	**ft_build_table(char const *s, char c, char **table, size_t i)
{
	size_t	j;
	size_t	k;
	size_t	len;

	j = 0;
	k = 0;
	while (j < i)
	{
		len = ft_wordlen(s, c, k);
		table[j] = (char *)ft_calloc((len + 1), sizeof(char));
		if (!(table[j]))
		{
			ft_free_table(table);
			return (NULL);
		}
		while (s[k] && s[k] == c)
			k++;
		if (s[k] && s[k] != c && ft_memcpy(table[j], (s + k), (len)))
			k += len;
		table[j][len + 1] = '\0';
		j++;
	}
	table[j] = NULL;
	return (table);
}

char	**ft_split(char const *s, char c)
{
	char	**table;
	size_t	i;

	i = ft_countwords(s, c);
	table = ft_calloc((i + 1), sizeof(char *));
	if (!(table))
		return (NULL);
	return (ft_build_table(s, c, table, i));
}
/*
int	main(void)
{
	const char	*string = "eaebhhgee fe  fe fwf e f f fer er  fw ee w e  er ";
	int			srchdc = 'e';
	char	**table = ft_split(string, srchdc);
	int	i = 0;
	while (table[i])
	{
		printf("%s\n", table[i]);
		i++;
	}
}*/	
