/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:24:45 by alsaeed           #+#    #+#             */
/*   Updated: 2023/11/14 15:54:19 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int		ft_atoi(char *num, int *error)
{
	int		i;
	long	res;

	res = 0;
	i = 0;
	while (num[i] == ' ' || (num[i] >= '\t' && num[i] <= '\r'))
		i++;
	if (num[i] == '-' || num[i] == '+')
	{
		if (num[i] == '-')
			*error = -1;
		i++;
	}
	if (num[i] == '+')
		*error = -1;
	while(num[i] >= '0' && num[i] <= '9')
	{
		res = res * 10 + num[i] - 48;
		if (res > 2147483647)
			*error = -1;
		i++;
	}
	return (res);
}
