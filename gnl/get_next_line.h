/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slatrech <slatrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:50:21 by slatrech          #+#    #+#             */
/*   Updated: 2025/01/14 14:52:45 by slatrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stddef.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h> 
# include <stdlib.h>
# include <string.h>
# include "../includes/libft.h"
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*ft_strdup(const char *src);

char	*ft_strjoin(char const *s1, char const *s2);

char	*get_next_line(int fd);

char	*ft_strtrim(char const *s1, char const *set);

char	*ft_substr(char const *s, unsigned int start, size_t len);
#endif