/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slatrech <slatrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:42:17 by slatrech          #+#    #+#             */
/*   Updated: 2025/08/06 14:42:18 by slatrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/built_ins.h"

int	export_loop(t_env **env, char **arg)
{
	int		i;
	char	*str;

	i = -1;
	ft_export(env, "EXIT_CODE=0");
	while (arg[++i])
	{
		ft_export(env, arg[i]);
		str = get_env(*env, "EXIT_CODE");
		if (ft_strcmp(str, "0"))
		{
			if (str)
			{
				free(str);
				str = NULL;
			}
			return (0);
		}
		if (str)
		{
			free(str);
			str = NULL;
		}
	}
	return (0);
}

int	find_equal_index(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	return (i);
}
