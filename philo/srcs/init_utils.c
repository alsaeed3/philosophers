/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 18:25:12 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/01 18:43:37 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_table	*fill_table(int philos_num)
{
	t_table	*table;

	table = ft_calloc(sizeof(t_table), 1);
	table->dead_philo = FALSE;
	table->fork_lock = ft_calloc(sizeof(pthread_mutex_t), \
						philos_num);
	table->fork_stat = ft_calloc(sizeof(t_bool), philos_num);
	table->fork_mask = ft_calloc(sizeof(int), philos_num);
	pthread_mutex_init(&table->print_lock, NULL);
	pthread_mutex_init(&table->time_lock, NULL);
	pthread_mutex_init(&table->table_lock, NULL);
	return (table);
}

void	init_philos(t_philo	**philo, char **input, int philos_num, \
		t_bool *error)
{
	int		i;
	t_table	*table;

	table = fill_table(philos_num);
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

void	fill_main(t_main *main)
{
	main->i = -1;
	main->j = -1;
	main->philos_num = 0;
	main->input = NULL;
	main->error = FALSE;
}
