/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flebrun <flebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:42:11 by slatrech          #+#    #+#             */
/*   Updated: 2025/08/06 16:22:41 by flebrun          ###   ########.fr       */
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
		if (ft_strcmp((*env)[i].key, "EXIT_CODE"))
		{
			if ((*env)[i].key)
				printf("%s=", (*env)[i].key);
			if ((*env)[i].value)
				printf("%s", (*env)[i].value);
			printf("\n");
		}
		i++;
	}
	return (0);
}
