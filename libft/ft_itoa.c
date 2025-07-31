#include "../includes/libft.h"

static size_t	ft_intlen(int n)
{
	size_t	i;

	i = 0;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	i++;
	return (i);
}

char	*ft_itoa(int nbr)
{
	char	*str;
	size_t	i;

	if (nbr == -2147483648)
	{
		str = (char *)ft_calloc(12, sizeof(char));
		if (!str)
			return (NULL);
		return (ft_memmove(str, "-2147483648", 12));
	}
	i = ft_intlen(nbr) + 1;
	str = (char *)ft_calloc(i, sizeof(char));
	if (!str)
		return (NULL);
	if (nbr < 0)
	{
		str[0] = '-';
		nbr *= -1;
	}
	while (i--, i > 0 && str[i - 1] != '-')
	{
		str[i - 1] = (nbr % 10) + 48;
		nbr = nbr / 10;
	}
	return (str);
}
/*
int main()
{
  int n = -2147483648;
  printf("%s\n", ft_itoa(n));
}*/
