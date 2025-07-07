#include "../includes/libft.h"

void	*ft_memset(void *p, int value, size_t count)
{
	unsigned char	*char_p;
	size_t			i;

	i = 0;
	char_p = (unsigned char *)p;
	while (i < count)
	{
		char_p[i] = (unsigned char)value;
		i++;
	}
	return (p);
}
