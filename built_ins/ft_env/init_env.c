/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slatrech <slatrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:42:15 by slatrech          #+#    #+#             */
/*   Updated: 2025/08/06 14:42:16 by slatrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/built_ins.h"

t_env	*init_new_env(int count)
{
	t_env	*new_env;
	int		i;

	new_env = malloc((sizeof(t_env)) * (count + 1));
	if (!new_env)
		return (NULL);
	i = -1;
	while (++i <= count)
	{
		new_env[i].key = NULL;
		new_env[i].value = NULL;
	}
	return (new_env);
}

int	init_env(char **envp, t_env **env)
{
	int		count;
	int		i;
	int		j;
	int		len;

	count = 0;
	while (envp[count])
		count++;
	*env = init_new_env(count + 1);
	if (!*env)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < count)
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		(*env)[i].key = ft_substr(envp[i], 0, j);
		len = ft_strlen(envp[i]) - j - 1;
		(*env)[i].value = ft_substr(envp[i], j + 1, len);
		i++;
	}
	(*env)[i].key = ft_strdup("EXIT_CODE");
	(*env)[i].value = ft_strdup("0");
	return (0);
}
