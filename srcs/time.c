/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:29:52 by alsaeed           #+#    #+#             */
/*   Updated: 2023/11/24 16:46:36 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	get_duration(struct timeval *prev_time)
{
	struct timeval curr_time;

	gettimeofday(&curr_time, NULL);
	return (((curr_time.tv_sec - prev_time->tv_sec) * 1000) \
		+ ((curr_time.tv_usec - prev_time->tv_usec) / 1000));
}

long	get_current_time(void)
{
	struct timeval	curr_time;

	gettimeofday(&curr_time, NULL);
	return ((curr_time.tv_sec * 1000000) + curr_time.tv_usec);
}

bool	eating_time(t_philo *philo)
{
	long	curr_time;
	long	meal_time;
	
	curr_time = get_current_time();
	meal_time = curr_time + (philo->table->time_eat * 1000);
	while (curr_time < meal_time)
	{
		if (is_dead(philo))
			return (true);
		curr_time = get_current_time();
	}
	return (false);
}

bool sleeping_time(t_philo *philo)
{
	long	curr_time;
	long	wake_time;

	trigger_on(philo, PHILO_LOCK);
	curr_time = get_current_time();
	wake_time = curr_time + (philo->table->time_sleep * 1000);
	while (curr_time < wake_time)
	{
		if (is_dead(philo))
			return (true);
		curr_time = get_current_time();
	}
	trigger_off(philo, PHILO_LOCK);
	return (false);
}
