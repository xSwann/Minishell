/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slatrech <slatrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:50:24 by slatrech          #+#    #+#             */
/*   Updated: 2025/01/14 14:11:43 by slatrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	s1len = ft_strlen((char *)s1);
	s2len = ft_strlen((char *)s2);
	ttlen = (s1len + s2len);
	nvl = malloc(sizeof(char) * ttlen + 1);
	if (!nvl)
		return (NULL);
	i = concat(s1, nvl, i, s1len);
	i = concat(s2, nvl, i, s2len);
	nvl[i] = '\0';
	return (nvl);
}
