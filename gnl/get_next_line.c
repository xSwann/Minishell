/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slatrech <slatrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:18:38 by slatrech          #+#    #+#             */
/*   Updated: 2025/07/31 14:48:53 by flebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	terminatingfinder(char *buffer, int j, int readreturn)
{
	while (buffer && buffer[j] != '\n' && buffer[j] != '\0' && j < readreturn)
		j++;
	if (!buffer)
		return (0);
	if (ft_strlen(buffer) == 1)
		return (0);
	return (j);
}

char	*zmata(char *ligne, char *buffer, size_t bufferindex, size_t readreturn)
{
	size_t	i;
	char	*sub;

	sub = ft_substr(buffer, bufferindex, (readreturn - bufferindex));
	i = terminatingfinder(sub, 0, ft_strlen(buffer));
	free(sub);
	sub = ft_substr(buffer, bufferindex, i + 1);
	ligne = ft_strjoin(ligne, sub);
	return (ligne);
}

size_t	add_buffer_left(char *buffer, size_t *id, int readreturn, char **ligne)
{
	size_t	len;
	char	*str;

	str = NULL;
	*ligne = NULL;
	if (*id < (size_t)readreturn && *id > 0 && readreturn > 0)
	{
		str = zmata(str, buffer, *id, readreturn);
		len = ft_strlen(str);
		if (str && buffer[len] != '\0')
		{
			if (len > 0 && str[len - 1] == '\n')
			{
				*ligne = str;
				*id += len;
				return (1);
			}
		}
		*ligne = str;
	}
	return (0);
}

size_t	join(char *buffer, char **ligne, int readreturn, size_t *indexstatic)
{
	char	*tmp;
	char	*tmp2;
	size_t	bufferindex;

	*indexstatic = 0;
	bufferindex = terminatingfinder(buffer, 0, readreturn - 1);
	tmp2 = ft_substr(buffer, 0, bufferindex + 1);
	if (*ligne)
	{
		tmp = ft_strjoin(*ligne, tmp2);
		free(tmp2);
		free(*ligne);
		*ligne = tmp;
	}
	else
		*ligne = tmp2;
	if (buffer[bufferindex] == '\n')
		(*indexstatic)++;
	return (bufferindex);
}

char	*get_next_line(int fd)
{
	static char		buffer[BUFFER_SIZE + 1];
	static size_t	indexstatic;
	static int		readreturn;
	size_t			bufferindex;
	char			*ligne;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bufferindex = add_buffer_left(buffer, &indexstatic, readreturn, &ligne);
	if (bufferindex != 0)
		return (ligne);
	readreturn = 0;
	while (readreturn == 0 || (buffer[bufferindex] != '\n' && readreturn > 0))
	{
		readreturn = read(fd, buffer, BUFFER_SIZE);
		if (readreturn == -1)
			return (free(ligne), NULL);
		if (readreturn == 0)
			return (ligne);
		bufferindex = join(buffer, &ligne, readreturn, &indexstatic);
	}
	indexstatic += bufferindex;
	return (ligne);
}

/* #include <stdio.h>
int main()
{
	char *line;
	int i = 0;
	int fd = open("test.txt", O_RDONLY);
	
	while(i <= 10)
	{
		line =get_next_line(fd);
		printf("%s", line);
		free(line);
		i++;
	}
	printf("\n");
	return (0);
} */

/* int	main()
{
	int	fd;
	fd = open("test.txt", O_RDONLY);
	// printf("2: %s", get_next_line(fd));
	// printf("3: %s", get_next_line(fd));
 	// printf("4: %s", get_next_line(fd));
	// printf("5: %s", get_next_line(fd));
	// printf("6: %s", get_next_line(fd));
	//printf("7%s", get_next_line(fd));
	//printf("8%s", get_next_line(fd));
	//printf("9%s", get_next_line(fd));
	//printf("10%s", get_next_line(fd));
	char *gnl;
	gnl = get_next_line(fd);
	while (gnl)
	{
		printf("%s", gnl);
		free(gnl);
		gnl = get_next_line(fd);
	}
} */
