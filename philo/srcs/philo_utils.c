/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:28:00 by alsaeed           #+#    #+#             */
/*   Updated: 2023/12/29 16:10:28 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	fill_table(t_table *table, int philos_num)
{
	table->dead_philo = FALSE;
	table->fork_lock = ft_calloc(sizeof(pthread_mutex_t), \
						philos_num);
	table->fork_stat = ft_calloc(sizeof(t_bool), philos_num);
	table->fork_mask = ft_calloc(sizeof(int), philos_num);
	pthread_mutex_init(&table->table_lock, NULL);
}

void	init_philos(t_philo	**philo, char **input, int philos_num, \
		t_bool *error)
{
	int		i;
	t_table	*table;

	table = ft_calloc(sizeof(t_table), 1);
	fill_table(table, philos_num);
	i = -1;
	while (++i < philos_num)
	{
		philo[i] = ft_calloc(sizeof(t_philo), 1);
		philo[i]->table = table;
		philo[i]->id = i + 1;
		philo[i]->table->fork_stat[i] = FALSE;
		philo[i]->table->fork_mask[i] = 0;
		philo[i]->philos_num = philos_num;
		philo[i]->time_die = ft_atoi(input[1], error);
		philo[i]->time_eat = ft_atoi(input[2], error);
		philo[i]->time_sleep = ft_atoi(input[3], error);
		pthread_mutex_init(&philo[i]->table->fork_lock[i], NULL);
		gettimeofday(&philo[i]->life_tv, NULL);
		philo[i]->life = get_current_time();
		if (ft_array_size(input) == 5)
			philo[i]->meals = ft_atoi(input[4], error);
		else
			philo[i]->meals = -1;
		philo[i]->table->total_meals = philo[i]->philos_num;
	}
}

t_bool	check_greedy(t_philo *philo)
{
	if (philo->id % philo->philos_num)
	{
		if (philo->table->fork_mask[philo->id - 1] == philo->id \
			|| philo->table->fork_mask[philo->id] == philo->id)
			return (FALSE);
	}
	else if (!(philo->id % philo->philos_num))
	{
		if (philo->table->fork_mask[0] == philo->id \
			|| philo->table->fork_mask[philo->id - 1] == philo->id)
			return (FALSE);
	}
	return (TRUE);
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
