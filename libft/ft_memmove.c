/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slatrech <slatrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:42:43 by slatrech          #+#    #+#             */
/*   Updated: 2025/08/06 14:42:44 by slatrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t size)
{
	unsigned char		*char_dst;
	const unsigned char	*char_src;
	size_t				i;

	char_dst = (unsigned char *)dst;
	char_src = (unsigned char *)src;
	if (char_dst < char_src)
	{
		i = 0;
		while (i < size)
		{
			char_dst[i] = char_src[i];
			i++;
		}
	}
	else if (char_dst > char_src)
	{
		i = (size);
		while (i > 0)
		{
			char_dst[i - 1] = char_src[i - 1];
			i--;
		}
	}
	return (dst);
}
/*
#include <string.h>
#include <stdlib.h>

int	main(void)
{
	char	buffer[] = "Hello Proxcop !";
	size_t	size = 9;

	printf("Avant ft_memmove avec chevauchement:\n");
    printf("Buffer: %s\n", buffer);

    // Déplacer "Hello" dans la zone du ", World!"
    ft_memmove(buffer, buffer + 5, size);

    printf("Après ft_memmove avec chevauchement:\n");
    printf("Buffer: %s\n", buffer);
}*/
