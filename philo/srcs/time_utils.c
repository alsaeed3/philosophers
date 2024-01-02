/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:29:52 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/02 14:52:17 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	get_duration(struct timeval *prev_time)
{
	struct timeval	curr_time;

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

t_bool	eating_time(t_philo *philo)
{
	long	curr_time;
	long	meal_time;

	curr_time = get_current_time();
	meal_time = curr_time + (philo->time_eat * 1000);
	while (curr_time < meal_time)
	{
		pthread_mutex_lock(&philo->table->dead_lock);
		if (philo->table->dead_philo)
		{
			pthread_mutex_unlock(&philo->table->dead_lock);
			return (TRUE);
		}
		pthread_mutex_unlock(&philo->table->dead_lock);
		curr_time = get_current_time();
		usleep(150);
	}
	return (FALSE);
}

t_bool	sleeping_time(t_philo *philo)
{
	long	curr_time;
	long	wake_time;

	curr_time = get_current_time();
	wake_time = curr_time + (philo->time_sleep * 1000);
	while (curr_time < wake_time)
	{
		pthread_mutex_lock(&philo->table->dead_lock);
		if (philo->table->dead_philo)
		{
			pthread_mutex_unlock(&philo->table->dead_lock);
			return (TRUE);
		}
		pthread_mutex_unlock(&philo->table->dead_lock);
		curr_time = get_current_time();
		usleep(150);
	}
	return (FALSE);
}
