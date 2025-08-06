/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slatrech <slatrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:43:07 by slatrech          #+#    #+#             */
/*   Updated: 2025/08/06 14:43:08 by slatrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*nvl;
	size_t	i;

	if (!s)
		return (NULL);
	if ((int)start >= ft_strlen((char *)s))
		return (ft_strdup(""));
	else if (len > ft_strlen((char *)s) - start)
		len = ft_strlen((char *)s) - start;
	nvl = malloc(sizeof(char) * len + 1);
	if (!nvl)
		return (NULL);
	i = 0;
	while ((i < len && s[start]) || (i == 0))
	{
		nvl[i] = s[start];
		i++;
		start++;
	}
	nvl[i] = '\0';
	return (nvl);
}
