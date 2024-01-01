/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:23:47 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/01 18:46:25 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_bool	ft_is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (TRUE);
	return (FALSE);
}

void	check_digit_after_space(char **av, int i, int j, t_bool *error)
{
	if (ft_is_digit(av[i][j]) && av[i][j + 1] == ' ')
	{
		while (av[i][++j] == ' ')
			;
		if (ft_is_digit(av[i][j]))
			*error = TRUE;
	}
}
