/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_modifiers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flebrun <flebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:54:46 by flebrun           #+#    #+#             */
/*   Updated: 2025/08/06 14:13:09 by flebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

char	**env_create(t_env **envp, int i, int is_exit_code)
{
	char	**env_str;

	if (!(*envp) || !(*envp)->key[0])
		return (NULL);
	while ((*envp)[i].key)
	{
		if (!ft_strcmp((*envp)[i++].key, "EXIT_CODE"))
			is_exit_code++;
	}
	env_str = malloc(sizeof (char *) * (i - is_exit_code + 1));
	if (!env_str)
		return (NULL);
	if (loop_duplicate(envp, env_str))
		return (NULL);
	free_env(envp);
	free(*envp);
	return (*envp = NULL, env_str[i - is_exit_code] = NULL, env_str);
}

int	close_fd(int *fd)
{
	if (fd && *fd >= 0)
	{
		if (close(*fd) == -1)
			return (*fd = -1, error_printer("close", "failed closing fd"), 1);
		*fd = -1;
	}
	return (0);
}

int	int_switcher(int *value_to_exchange)
{
	int	value_to_return;

	value_to_return = *value_to_exchange;
	*value_to_exchange = 0;
	return (value_to_return);
}
