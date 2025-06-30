
#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	size_t			i;
	unsigned char	*array;

	i = 0;
	if (n * size > 2147483647)
		return (NULL);
	array = malloc(n * size);
	if (!array)
		return (NULL);
	while (i < (n * size))
	{
		array[i] = 0;
		i++;
	}
	return ((void *)array);
}
/*
int	main(void)
{
	int	*array;
	int	i;
	int	*array2;
	int	i2;

	array = ft_calloc(5, sizeof(int));
	i = 0;
	printf("ft_calloc : ");
	while (array[i])
	{
		printf("%d ", array[i]);
		i++;
	}
	array2 = calloc(5, sizeof(int));
	i2 = 0;
	printf("\ncalloc : ");
	while (array2[i2])
	{
		printf("%d ", array[i2]);
		i2++;
	}
}*/
