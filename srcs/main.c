/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 20:56:15 by alsaeed           #+#    #+#             */
/*   Updated: 2023/11/25 14:17:26 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	eat_noodles(t_philo *philo)
{
	trigger_on(philo, FORK_STAT);
	trigger_on(philo, FORK_MASK);
	philo->life = get_duration(&philo->life_tv);
	trigger_on(philo, FORK_LOCK);
	display_log(philo, TAKE);
	display_log(philo, TAKE);
	display_log(philo, EAT);
	philo->meals--;
	if (eating_time(philo))
		return (true);
	trigger_off(philo, FORK_LOCK);
	trigger_off(philo, FORK_STAT);
	display_log(philo, SLEEP);
	if (sleeping_time(philo))
		return (true);
	display_log(philo, THINK);
	return (false);
}

bool	mask_fork(t_philo *philo)
{
	if (philo->id % philo->table->philos_num)
	{
		if (philo->table->fork_mask[philo->id - 1] == philo->id)
			return (false);
	}
	else if (!(philo->id % philo->table->philos_num))
	{
		if (philo->table->fork_mask[philo->id - 1] == philo->id)
			return (false);
	}
	return (true);
}

void	*routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	if (philo->table->philos_num == 1)
		return (single_philo(philo));
	while (1)
	{
		if (is_dead(philo) || !philo->meals)
			break ;
		trigger_off(philo, FORK_LOCK);
		if ((philo->id % philo->table->philos_num) && !philo->table->fork_stat[philo->id - 1] && !philo->table->fork_stat[philo->id] && philo->meals && mask_fork(philo))
		{
			if (eat_noodles(philo))
				return (NULL);
		}
		else if (!(philo->id % philo->table->philos_num) && !philo->table->fork_stat[philo->id - 1] &&!philo->table->fork_stat[0] && philo->meals && mask_fork(philo))
		{
			if (eat_noodles(philo))
				return (NULL);
		}
		trigger_on(philo, FORK_LOCK);
		usleep(50);
	}
	return (NULL);
}

void	fill_table(t_table *table, char **input, int i)
{
	table->dead_philo = false;
	table->philos_num = ft_atoi(input[0], &i);
	table->time_die = ft_atoi(input[1], &i);
	table->time_eat = ft_atoi(input[2], &i);
	table->time_sleep = ft_atoi(input[3], &i);
	table->fork_lock = ft_calloc(sizeof(pthread_mutex_t), table->philos_num);
	table->fork_stat = ft_calloc(sizeof(bool), table->philos_num);
	table->fork_mask = ft_calloc(sizeof(int), table->philos_num);
	pthread_mutex_init(&table->table_lock, NULL);
}

void	init_philos(t_philo	**philo, char **input, int ac)
{
	int		i;
	t_table	*table;

	i = 0;
	table = ft_calloc(sizeof(t_table), 1);
	fill_table(table, input, i);
	while (i < ft_atoi(input[0], &i))
	{
		philo[i] = ft_calloc(sizeof(t_philo), 1);
		philo[i]->table = table;
		philo[i]->id = i + 1;
		philo[i]->table->fork_stat[i] = false;
		philo[i]->table->fork_mask[i] = 0;
		pthread_mutex_init(&philo[i]->table->fork_lock[i], NULL);
		gettimeofday(&philo[i]->life_tv, NULL);
		philo[i]->life = get_duration(&philo[i]->life_tv);
		if (ac == 6)
			philo[i]->meals = ft_atoi(input[4], &i);
		else
			philo[i]->meals = -1;
		i++;
	}
}

void	cleanup(t_philo **philos, char **input, int range)
{
	int	i;

	free_array(input);
	free((*philos)->table->fork_stat);
	free((*philos)->table->fork_mask);
	free((*philos)->table->fork_lock);
	free((*philos)->table);
	i = -1;
	while (++i < range)
	{
		free(philos[i]);
		philos[i] = NULL;
	}
	if (philos)
	{
		free(philos);
		philos = NULL;
	}
}

int main(int ac, char **av)
{
	t_philo		**philo;
	char		**input;
	int			i;

	input = NULL;
	if (ac == 5 || ac == 6)
	{
		input = parse_args(ac, av);
		philo = ft_calloc(sizeof(t_philo *), ft_atoi(input[0], &i));
		init_philos(philo, input, ac);
		i = -1;
		while (++i < ft_atoi(input[0], &i))
		{
			pthread_create(&philo[i]->thread, NULL, routine, philo[i]);
			usleep(350);
		}
		i = -1;
		while (++i < ft_atoi(input[0], &i))
			pthread_join(philo[i]->thread, NULL);
		cleanup(philo, input, philo[0]->table->philos_num);
		return (0);
	}
	printf("Error: Invalid number of arguments\n");
	return (1);
}
