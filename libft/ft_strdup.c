
#include "../includes/libft.h"

char	*ft_strdup(const char *src)
{
	char	*nvl;
	int		len;
	int		i;

	if (!src)
		return (NULL);
	len = 0;
	i = 0;
	while (src[len])
		len++;
	nvl = malloc(sizeof(char) * len + 1);
	if (!nvl)
		return (NULL);
	while (src[i])
	{
		nvl[i] = src[i];
		i++;
	}
	nvl[i] = '\0';
	return (nvl);
}
