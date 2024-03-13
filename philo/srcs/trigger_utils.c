/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigger_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 19:03:08 by alsaeed           #+#    #+#             */
/*   Updated: 2024/03/14 02:00:29 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	trigger_off(t_philo *philo, int flag)
{
	pthread_mutex_lock(&philo->table->table_lock);
	if ((flag == FORK_LOCK) && (philo->id % philo->philos_num))
	{
		pthread_mutex_unlock(&philo->table->fork_lock[philo->id - 1]);
		pthread_mutex_unlock(&philo->table->fork_lock[philo->id]);
	}
	else if ((flag == FORK_LOCK) && !(philo->id % philo->philos_num))
	{
		pthread_mutex_unlock(&philo->table->fork_lock[0]);
		pthread_mutex_unlock(&philo->table->fork_lock[philo->id - 1]);
	}
	pthread_mutex_unlock(&philo->table->table_lock);
}

void	trigger_on(t_philo *philo, int flag)
{
	if ((flag == FORK_LOCK) && (philo->id % philo->philos_num))
	{
		pthread_mutex_lock(&philo->table->fork_lock[philo->id - 1]);
		pthread_mutex_lock(&philo->table->fork_lock[philo->id]);
	}
	else if ((flag == FORK_LOCK) && !(philo->id % philo->philos_num))
	{
		pthread_mutex_lock(&philo->table->fork_lock[0]);
		pthread_mutex_lock(&philo->table->fork_lock[philo->id - 1]);
	}
	else if ((flag == FORK_MASK) && (philo->id % philo->philos_num))
	{
		pthread_mutex_lock(&philo->table->table_lock);
		philo->table->fork_mask[philo->id - 1] = philo->id;
		philo->table->fork_mask[philo->id] = philo->id;
		pthread_mutex_unlock(&philo->table->table_lock);
	}
	else if ((flag == FORK_MASK) && !(philo->id % philo->philos_num))
	{
		pthread_mutex_lock(&philo->table->table_lock);
		philo->table->fork_mask[0] = philo->id;
		philo->table->fork_mask[philo->id - 1] = philo->id;
		pthread_mutex_unlock(&philo->table->table_lock);
	}
}

t_bool	is_dead(t_philo *philo)
{
	usleep(20);
	pthread_mutex_lock(&philo->table->dead_lock);
	if (philo->table->dead_philo)
	{
		pthread_mutex_unlock(&philo->table->dead_lock);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->table->dead_lock);
	return (FALSE);
}

t_bool	total_meals_check(t_philo *philo)
{
	usleep(20);
	pthread_mutex_lock(&philo->table->meals_lock);
	if (philo->table->total_meals)
	{
		pthread_mutex_unlock(&philo->table->meals_lock);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->table->meals_lock);
	return (FALSE);
}
