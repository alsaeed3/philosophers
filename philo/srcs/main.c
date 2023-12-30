/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 20:56:15 by alsaeed           #+#    #+#             */
/*   Updated: 2023/12/30 18:26:35 by alsaeed          ###   ########.fr       */
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
			pthread_mutex_unlock(&philo->table->table_lock);
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

void	fill_main(t_main *main)
{
	main->i = -1;
	main->j = -1;
	main->philos_num = 0;
	main->input = NULL;
	main->error = FALSE;
}

int	main(int ac, char **av)
{
	t_main	main;

	fill_main(&main);
	if (ac == 5 || ac == 6)
	{
		main.input = parse_args(ac, av, &main.error);
		if (main.error)
			return (1);
		main.philos_num = ft_atoi(main.input[0], &main.error);
		main.philo = ft_calloc(sizeof(t_philo *), main.philos_num);
		init_philos(main.philo, main.input, main.philos_num, &main.error);
		while (++main.i < main.philos_num)
		{
			if (pthread_create(&main.philo[main.i]->thread, NULL, \
				routine, main.philo[main.i]))
				return (0);
			usleep(350);
		}
		while (++main.j < main.philos_num)
			pthread_join(main.philo[main.j]->thread, NULL);
		cleanup(main.philo, main.input, main.philos_num);
		return (0);
	}
	printf("Error\nInvalid number of arguments\n");
	return (1);
}
