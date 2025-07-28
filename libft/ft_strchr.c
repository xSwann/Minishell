#include "../includes/libft.h"

char	*ft_strchr(const char *string, int searchedchar)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == (char)searchedchar)
			return ((char *)(string + i));
		else
			i++;
	}
	if ((char)searchedchar == '\0')
		return ((char *)(string + i));
	return (NULL);
}
/*
#include <stdlib.h>
#include <string.h>

int	main(int ac, char **av)
{
	(void)ac;
	printf("Result of ft_strchr : %s  ", ft_strchr(av[1], av[2][0]));
	printf("Result of strchr : %s  ", strchr(av[1], av[2][0]));
}*/
