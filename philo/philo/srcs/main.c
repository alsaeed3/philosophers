/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 20:56:15 by alsaeed           #+#    #+#             */
/*   Updated: 2023/12/29 17:34:45 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_bool	eat_noodles(t_philo *philo)
{
	trigger_on(philo, FORK_STAT);
	trigger_on(philo, FORK_MASK);
	philo->life = get_duration(&philo->life_tv);
	trigger_off(philo, FORK_LOCK);
	display_log(philo, TAKE);
	display_log(philo, TAKE);
	display_log(philo, EAT);
	philo->meals--;
	pthread_mutex_lock(&philo->table->table_lock);
	if (!philo->meals)
		philo->table->total_meals--;
	if (!philo->table->total_meals)
	{
		pthread_mutex_unlock(&philo->table->table_lock);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->table->table_lock);
	if (eating_time(philo))
		return (TRUE);
	if (sleep_bro(philo))
		return (TRUE);
	trigger_on(philo, FORK_LOCK);
	display_log(philo, THINK);
	return (FALSE);
}

t_bool	sleep_bro(t_philo *philo)
{
	trigger_on(philo, FORK_LOCK);
	trigger_off(philo, FORK_STAT);
	display_log(philo, SLEEP);
	trigger_off(philo, FORK_LOCK);
	if (sleeping_time(philo))
		return (TRUE);
	return (FALSE);
}

t_bool	check_eating(t_philo *philo)
{
	if ((philo->id % philo->philos_num) \
		&& !philo->table->fork_stat[philo->id - 1] \
		&& !philo->table->fork_stat[philo->id] \
		&& philo->meals && check_greedy(philo))
	{
		if (eat_noodles(philo))
			return (TRUE);
	}
	else if (!(philo->id % philo->philos_num) \
			&& !philo->table->fork_stat[0] \
			&& !philo->table->fork_stat[philo->id - 1] && philo->meals \
			&& check_greedy(philo))
	{
		if (eat_noodles(philo))
			return (TRUE);
	}
	return (FALSE);
}

void	*routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	if (philo->philos_num == 1)
		return (single_philo(philo));
	while (1)
	{
		pthread_mutex_lock(&philo->table->table_lock);
		if (!philo->table->total_meals)
		{
			printf("-------------> philo %d is done\n", philo->id);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->table->table_lock);
		if (is_dead(philo) || !philo->meals)
			break ;
		trigger_on(philo, FORK_LOCK);
		if (check_eating(philo))
			return (NULL);
		trigger_off(philo, FORK_LOCK);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_philo		**philo;
	char		**input;
	int			i;
	int			philos_num;
	t_bool		error;

	input = NULL;
	error = FALSE;
	if (ac == 5 || ac == 6)
	{
		input = parse_args(ac, av, &error);
		i = -1;
		if (error)
			return (1);
		philos_num = ft_atoi(input[0], &error);
		if (error)
			return (1);
		philo = ft_calloc(sizeof(t_philo *), philos_num);
		init_philos(philo, input, philos_num, &error);
		i = -1;
		while (++i < philos_num)
		{
			if (pthread_create(&philo[i]->thread, NULL, routine, philo[i]))
				return (0);
			usleep(350);
		}
		i = -1;
		while (++i < philos_num)
			pthread_join(philo[i]->thread, NULL);
		cleanup(philo, input, philos_num);
		return (0);
	}
	printf("Error\nInvalid number of arguments\n");
	return (1);
}
