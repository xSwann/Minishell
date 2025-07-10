
#include "../includes/libft.h"

int	concat(const char *ch, char *nv, size_t in, size_t len)
{
	size_t	j;

	j = 0;
	while (j < len)
	{
		nv[in] = ch[j];
		in++;
		j++;
	}
	return (in);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t			s1len;
	size_t			s2len;
	static size_t	ttlen;
	size_t			i;
	char			*nvl;

	i = 0;
	s1len = 0;
	s2len = 0;
	while (s1 && s1[s1len])
		s1len++;
	while (s2 && s2[s2len])
		s2len++;
	ttlen = (s1len + s2len);
	nvl = malloc(sizeof(char) * ttlen + 1);
	if (!nvl)
		return (NULL);
	i = concat(s1, nvl, i, s1len);
	i = concat(s2, nvl, i, s2len);
	nvl[i] = '\0';
	return (nvl);
}
