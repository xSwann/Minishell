/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slatrech <slatrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:42:06 by slatrech          #+#    #+#             */
/*   Updated: 2025/08/06 14:42:07 by slatrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/built_ins.h"

void	free_env(t_env **env)
{
	int	i;

	i = 0;
	if (!env || !*env)
		return ;
	while ((*env)[i].key)
	{
		if ((*env)[i].key)
		{
			free((*env)[i].key);
			(*env)[i].key = NULL;
		}
		if ((*env)[i].value)
		{
			free((*env)[i].value);
			(*env)[i].value = NULL;
		}
		i++;
	}
	free(*env);
	*env = NULL;
}
