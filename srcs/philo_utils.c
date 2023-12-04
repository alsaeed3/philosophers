/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:28:00 by alsaeed           #+#    #+#             */
/*   Updated: 2023/11/28 18:32:00 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	fill_table(t_table *table, char **input)
{
	int	i;

	i = 0;
	table->dead_philo = false;
	table->fork_lock = ft_calloc(sizeof(pthread_mutex_t), \
						ft_atoi(input[0], &i));
	table->fork_stat = ft_calloc(sizeof(bool), ft_atoi(input[0], &i));
	table->fork_mask = ft_calloc(sizeof(int), ft_atoi(input[0], &i));
	pthread_mutex_init(&table->table_lock, NULL);
}

void	init_philos(t_philo	**philo, char **input, int ac)
{
	int		i;
	t_table	*table;

	table = ft_calloc(sizeof(t_table), 1);
	fill_table(table, input);
	i = -1;
	while (++i < ft_atoi(input[0], &i))
	{
		philo[i] = ft_calloc(sizeof(t_philo), 1);
		philo[i]->table = table;
		philo[i]->id = i + 1;
		philo[i]->table->fork_stat[i] = false;
		philo[i]->table->fork_mask[i] = 0;
		philo[i]->philos_num = ft_atoi(input[0], &i);
		philo[i]->time_die = ft_atoi(input[1], &i);
		philo[i]->time_eat = ft_atoi(input[2], &i);
		philo[i]->time_sleep = ft_atoi(input[3], &i);
		pthread_mutex_init(&philo[i]->table->fork_lock[i], NULL);
		gettimeofday(&philo[i]->life_tv, NULL);
		philo[i]->life = get_current_time();
		if (ac == 6)
			philo[i]->meals = ft_atoi(input[4], &i);
		else
			philo[i]->meals = -1;
	}
}

bool	check_greedy(t_philo *philo)
{
	usleep(32);
	if (philo->id % philo->philos_num)
	{
		if (philo->table->fork_mask[philo->id - 1] == philo->id \
			|| philo->table->fork_mask[philo->id] == philo->id)
			return (false);
	}
	else if (!(philo->id % philo->philos_num))
	{
		if (philo->table->fork_mask[0] == philo->id \
			|| philo->table->fork_mask[philo->id - 1] == philo->id)
			return (false);
	}
	return (true);
}

void	*single_philo(t_philo *philo)
{
	long	curr_time;
	long	deadline;

	if (!philo->meals)
		return (NULL);
	curr_time = get_current_time();
	deadline = curr_time + (philo->time_die * 1000);
	while (curr_time < deadline)
		curr_time = get_current_time();
	printf("%lu %d died\n", get_duration(&philo->life_tv), philo->id);
	return (NULL);
}
