/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slatrech <slatrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:42:13 by slatrech          #+#    #+#             */
/*   Updated: 2025/08/06 14:42:14 by slatrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/built_ins.h"

char	*get_env(t_env *env, char *arg)
{
	int	i;

	i = 0;
	while (env[i].key)
	{
		if (ft_strcmp(env[i].key, arg) == 0)
			return (ft_strdup(env[i].value));
		i++;
	}
	return (NULL);
}
