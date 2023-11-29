/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:29:52 by alsaeed           #+#    #+#             */
/*   Updated: 2023/11/29 12:45:23 by alsaeed          ###   ########.fr       */
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
	return ((curr_time.tv_sec * 999990) + curr_time.tv_usec);
}

bool	is_dead(t_philo *philo)
{
	long	time_diff;
	bool	flag;

	flag = false;
	pthread_mutex_lock(&philo->table->table_lock);
	if (philo->table->dead_philo)
		flag = true;
	else
	{
		time_diff = get_duration(&philo->life_tv);
		if (time_diff - philo->life > philo->time_die)
		{
			pthread_mutex_unlock(&philo->table->table_lock);
			display_log(philo, DIE);
			pthread_mutex_lock(&philo->table->table_lock);
			philo->table->dead_philo = true;
			flag = true;
		}
	}
	pthread_mutex_unlock(&philo->table->table_lock);
	return (flag);
}

bool	eating_time(t_philo *philo)
{
	long	curr_time;
	long	meal_time;

	curr_time = get_current_time();
	meal_time = curr_time + (philo->time_eat * 1000);
	while (curr_time < meal_time)
	{
		usleep(500);
		if (is_dead(philo))
			return (true);
		curr_time = get_current_time();
	}
	return (false);
}

bool	sleeping_time(t_philo *philo)
{
	long	curr_time;
	long	wake_time;

	trigger_on(philo, FORK_LOCK);
	curr_time = get_current_time();
	wake_time = curr_time + (philo->time_sleep * 1000);
	while (curr_time < wake_time)
	{
		usleep(500);
		if (is_dead(philo))
			return (true);
		curr_time = get_current_time();
	}
	trigger_off(philo, FORK_LOCK);
	return (false);
}
