/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:20:55 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/02 14:36:09 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	display_log(t_philo *philo, int stat)
{
	pthread_mutex_lock(&philo->table->print_lock);
	if (!is_dead(philo))
	{
		printf("%lu %d", get_duration(&philo->life_tv), philo->id);
		if (stat == TAKE)
			printf(" has taken a fork\n");
		else if (stat == EAT)
			printf(" is eating\n");
		else if (stat == SLEEP)
			printf(" is sleeping\n");
		else if (stat == THINK)
			printf(" is thinking\n");
		else if (stat == DIE)
			printf(" died\n");
	}
	pthread_mutex_unlock(&philo->table->print_lock);
}
