#include "libft.h"

int	ft_strncmp(char *s1, char *s2, size_t l)
{
	unsigned char	c1;
	unsigned char	c2;
	size_t			i;

	i = 0;
	while (i < l && (s1[i] || s2[i]))
	{
		c1 = (unsigned char)s1[i];
		c2 = (unsigned char)s2[i];
		if (c1 != c2)
			return (c1 - c2);
		i++;
	}
	return (0);
}
/*
#include <string.h>
#include <stdlib.h>

int	main(int ac, char **av)
{
	size_t	l = (size_t)atoi(av[3]);

	(void)ac;
	printf("Resultat ft_strncmp %d\n", ft_strncmp(av[1], av[2], l));
	printf("Resultat strncmp %d\n", strncmp(av[1], av[2], l));
}*/
