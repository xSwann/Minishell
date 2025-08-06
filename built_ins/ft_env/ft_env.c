/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slatrech <slatrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:42:11 by slatrech          #+#    #+#             */
/*   Updated: 2025/08/06 14:42:12 by slatrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/built_ins.h"

int	ft_env(t_env **env, char **arg)
{
	int	i;

	i = 0;
	if (arg && arg[0])
		return (1);
	while ((*env)[i].key)
	{
		if ((*env)[i].key)
			printf("%s=", (*env)[i].key);
		if ((*env)[i].value)
			printf("%s", (*env)[i].value);
		printf("\n");
		i++;
	}
	return (0);
}
