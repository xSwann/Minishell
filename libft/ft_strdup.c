/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slatrech <slatrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:42:56 by slatrech          #+#    #+#             */
/*   Updated: 2025/08/06 14:42:57 by slatrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
