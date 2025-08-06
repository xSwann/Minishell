/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slatrech <slatrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:42:23 by slatrech          #+#    #+#             */
/*   Updated: 2025/08/06 14:42:24 by slatrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/built_ins.h"

int	unset_loop(t_env **env, char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (ft_unset(env, arg[i]))
			return (ft_export(env, "EXIT_CODE=1"), 1);
		i++;
	}
	return (0);
}
