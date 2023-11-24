/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:34:05 by alsaeed           #+#    #+#             */
/*   Updated: 2023/11/24 19:08:17 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	display_log(t_philo *philo, int stat)
{
	pthread_mutex_lock(&philo->table->table_lock);
	pthread_mutex_lock(&philo->table->print_lock);
	if (!philo->table->dead_philo)
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
		{
			printf(" died\n");
			philo->table->dead_philo = true;
		}
	}
	pthread_mutex_unlock(&philo->table->print_lock);
	pthread_mutex_unlock(&philo->table->table_lock);
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
		if (time_diff - philo->life > philo->table->time_die)
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

void	*single_philo(t_philo *philo)
{
	long	curr_time;
	long	deadline;

	curr_time = get_current_time();
	deadline = curr_time + (philo->table->time_die * 1000);
	while (curr_time < deadline)
		curr_time = get_current_time();
	printf("%lu %d died\n", get_duration(&philo->life_tv), philo->id);
	return (NULL);
}

void	trigger_on(t_philo *philo, int flag)
{
	if ((flag == PHILO_LOCK) && (philo->id % philo->table->philos_num))
	{
		pthread_mutex_unlock(&philo->table->philo_lock[philo->id - 1]);
		pthread_mutex_unlock(&philo->table->philo_lock[philo->id]);
	}
	else if ((flag == PHILO_LOCK) && !(philo->id % philo->table->philos_num))
	{
		pthread_mutex_unlock(&philo->table->philo_lock[philo->id - 1]);
		pthread_mutex_unlock(&philo->table->philo_lock[0]);
	}
	else if ((flag == FORK_STAT) && (philo->id % philo->table->philos_num))
	{
		philo->table->fork_stat[philo->id - 1] = true;
		philo->table->fork_stat[philo->id] = true;
	}
	else if ((flag == FORK_STAT) && !(philo->id % philo->table->philos_num))
	{
		philo->table->fork_stat[philo->id - 1] = true;
		philo->table->fork_stat[0] = true;
	}
	else
		trigger_mask(philo, true);
}

void	trigger_off(t_philo *philo, int flag)
{
	if ((flag == PHILO_LOCK) && (philo->id % philo->table->philos_num))
	{
		pthread_mutex_lock(&philo->table->philo_lock[philo->id - 1]);
		pthread_mutex_lock(&philo->table->philo_lock[philo->id]);
	}
	else if ((flag == PHILO_LOCK) && !(philo->id % philo->table->philos_num))
	{
		pthread_mutex_lock(&philo->table->philo_lock[philo->id - 1]);
		pthread_mutex_lock(&philo->table->philo_lock[0]);
	}
	else if ((flag == FORK_STAT) && (philo->id % philo->table->philos_num))
	{
		philo->table->fork_stat[philo->id - 1] = false;
		philo->table->fork_stat[philo->id] = false;
	}
	else if ((flag == FORK_STAT) && !(philo->id % philo->table->philos_num))
	{
		philo->table->fork_stat[philo->id - 1] = false;
		philo->table->fork_stat[0] = false;
	}
	else
		trigger_mask(philo, false);
}

void	trigger_mask(t_philo *philo, bool trigger)
{
	if (!trigger && (philo->id % philo->table->philos_num))
	{
		philo->table->fork_mask[philo->id - 1] = 0;
		philo->table->fork_mask[philo->id] = 0;
	}
	else if (!trigger && !(philo->id % philo->table->philos_num))
	{
		philo->table->fork_mask[philo->id - 1] = 0;
		philo->table->fork_mask[0] = 0;
	}
	else if (trigger && (philo->id % philo->table->philos_num))
	{
		philo->table->fork_mask[philo->id - 1] = philo->id;
		philo->table->fork_mask[philo->id] = philo->id;
	}
	else if (trigger && !(philo->id % philo->table->philos_num))
	{
		philo->table->fork_mask[philo->id - 1] = philo->id;
		philo->table->fork_mask[0] = philo->id;
	}
}
