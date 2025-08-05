/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_modifiers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flebrun <flebrun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:54:46 by flebrun           #+#    #+#             */
/*   Updated: 2025/08/05 17:56:23 by flebrun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

int	int_switcher(int *value_to_exchange)
{
	int	value_to_return;

	value_to_return = *value_to_exchange;
	*value_to_exchange = 0;
	return (value_to_return);
}
