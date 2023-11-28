/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigger_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 19:03:08 by alsaeed           #+#    #+#             */
/*   Updated: 2023/11/28 14:51:54 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	trigger_on(t_philo *philo, int flag)
{
	if ((flag == FORK_LOCK) && (philo->id % philo->philos_num))
	{
		pthread_mutex_unlock(&philo->table->fork_lock[philo->id - 1]);
		pthread_mutex_unlock(&philo->table->fork_lock[philo->id]);
	}
	else if ((flag == FORK_LOCK) && !(philo->id % philo->philos_num))
	{
		pthread_mutex_unlock(&philo->table->fork_lock[philo->id - 1]);
		pthread_mutex_unlock(&philo->table->fork_lock[0]);
	}
	else if ((flag == FORK_STAT) && (philo->id % philo->philos_num))
	{
		philo->table->fork_stat[philo->id - 1] = true;
		philo->table->fork_stat[philo->id] = true;
	}
	else if ((flag == FORK_STAT) && !(philo->id % philo->philos_num))
	{
		philo->table->fork_stat[philo->id - 1] = true;
		philo->table->fork_stat[0] = true;
	}
	else if (flag == FORK_MASK)
		trigger_mask(philo);
}

void	trigger_mask(t_philo *philo)
{
	if (philo->id % philo->philos_num)
	{
		philo->table->fork_mask[philo->id - 1] = philo->id;
		philo->table->fork_mask[philo->id] = philo->id;
	}
	else
	{
		philo->table->fork_mask[philo->id - 1] = philo->id;
		philo->table->fork_mask[0] = philo->id;
	}
}

void	trigger_off(t_philo *philo, int flag)
{
	if ((flag == FORK_LOCK) && (philo->id % philo->philos_num))
	{
		pthread_mutex_lock(&philo->table->fork_lock[philo->id - 1]);
		pthread_mutex_lock(&philo->table->fork_lock[philo->id]);
	}
	else if ((flag == FORK_LOCK) && !(philo->id % philo->philos_num))
	{
		pthread_mutex_lock(&philo->table->fork_lock[philo->id - 1]);
		pthread_mutex_lock(&philo->table->fork_lock[0]);
	}
	else if ((flag == FORK_STAT) && (philo->id % philo->philos_num))
	{
		philo->table->fork_stat[philo->id - 1] = false;
		philo->table->fork_stat[philo->id] = false;
	}
	else if ((flag == FORK_STAT) && !(philo->id % philo->philos_num))
	{
		philo->table->fork_stat[philo->id - 1] = false;
		philo->table->fork_stat[0] = false;
	}
}
