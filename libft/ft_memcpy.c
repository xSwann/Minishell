/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flebrun <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 09:20:55 by flebrun           #+#    #+#             */
/*   Updated: 2024/12/02 10:52:14 by flebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *source, size_t size)
{
	unsigned char	*char_dest;
	unsigned char	*char_source;
	size_t			i;

	if (!dest && !source)
		return (NULL);
	i = 0;
	char_dest = (unsigned char *)dest;
	char_source = (unsigned char *)source;
	while (i < size)
	{
		char_dest[i] = char_source[i];
		i++;
	}
	return (dest);
}
/*
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int	main()
{
	char	*array = NULL;
	size_t	size = 10;
	char	*copy = NULL;
	int		i;
	printf("%s\n", copy);
	ft_memcpy(copy, array, size);
	printf("%s\n", copy);
}*/
