/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:28:00 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/01 20:38:43 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_bool	check_greedy(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->table_lock);
	if (philo->id % philo->philos_num)
	{
		if (philo->table->fork_mask[philo->id - 1] == philo->id \
			|| philo->table->fork_mask[philo->id] == philo->id)
		{
			pthread_mutex_unlock(&philo->table->table_lock);
			return (TRUE);
		}
	}
	else
	{
		if (philo->table->fork_mask[0] == philo->id \
			|| philo->table->fork_mask[philo->id - 1] == philo->id)
		{
			pthread_mutex_unlock(&philo->table->table_lock);
			return (TRUE);
		}
	}
	pthread_mutex_unlock(&philo->table->table_lock);
	return (FALSE);
}

void	*single_philo(t_philo *philo)
{
	long	curr_time;
	long	deadline;

	curr_time = get_current_time();
	deadline = curr_time + (philo->time_die * 1000);
	while (curr_time < deadline)
		curr_time = get_current_time();
	printf("%lu %d died\n", get_duration(&philo->life_tv), philo->id);
	return (NULL);
}

t_bool	sleep_bro(t_philo *philo)
{
	display_log(philo, SLEEP);
	if (sleeping_time(philo))
		return (TRUE);
	return (FALSE);
}
