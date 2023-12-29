/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigger_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 19:03:08 by alsaeed           #+#    #+#             */
/*   Updated: 2023/12/28 19:16:19 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	trigger_off(t_philo *philo, int flag)
{
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
	else if ((flag == FORK_STAT) && (philo->id % philo->philos_num))
	{
		philo->table->fork_stat[philo->id - 1] = FALSE;
		philo->table->fork_stat[philo->id] = FALSE;
	}
	else if ((flag == FORK_STAT) && !(philo->id % philo->philos_num))
	{
		philo->table->fork_stat[0] = FALSE;
		philo->table->fork_stat[philo->id - 1] = FALSE;
	}
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
	else if ((flag == FORK_STAT) && (philo->id % philo->philos_num))
	{
		philo->table->fork_stat[philo->id - 1] = TRUE;
		philo->table->fork_stat[philo->id] = TRUE;
	}
	else if ((flag == FORK_STAT) && !(philo->id % philo->philos_num))
	{
		philo->table->fork_stat[0] = TRUE;
		philo->table->fork_stat[philo->id - 1] = TRUE;
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
		philo->table->fork_mask[0] = philo->id;
		philo->table->fork_mask[philo->id - 1] = philo->id;
	}
}
