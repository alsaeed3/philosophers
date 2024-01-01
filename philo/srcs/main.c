/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 20:56:15 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/01 18:51:06 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	if (philo->philos_num == 1)
		return (single_philo(philo));
	if (!(philo->id % 2))
		usleep(100);
	while (!is_dead(philo) && total_meals_check(philo))
	{
		if (eat_noodles(philo))
			break ;
	}
	return (NULL);
}

t_bool	eat_noodles(t_philo *philo)
{
	if (check_greedy(philo))
		return (FALSE);
	trigger_on(philo, FORK_LOCK);
	if (cont_eat_noodles(philo))
		return (TRUE);
	if (eating_time(philo))
	{
		trigger_off(philo, FORK_LOCK);
		return (TRUE);
	}
	trigger_off(philo, FORK_LOCK);
	philo->meals--;
	pthread_mutex_lock(&philo->table->table_lock);
	if (!philo->meals)
		philo->table->total_meals--;
	pthread_mutex_unlock(&philo->table->table_lock);
	if (sleep_bro(philo))
		return (TRUE);
	display_log(philo, THINK);
	return (FALSE);
}

t_bool	cont_eat_noodles(t_philo *philo)
{	
	pthread_mutex_lock(&philo->table->table_lock);
	if (!philo->table->total_meals)
	{
		pthread_mutex_unlock(&philo->table->table_lock);
		trigger_off(philo, FORK_LOCK);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->table->table_lock);
	trigger_on(philo, FORK_MASK);
	pthread_mutex_lock(&philo->table->time_lock);
	philo->life = get_duration(&philo->life_tv);
	pthread_mutex_unlock(&philo->table->time_lock);
	display_log(philo, TAKE);
	display_log(philo, TAKE);
	display_log(philo, EAT);
	return (FALSE);
}

void	inspecting_philos(t_philo **philo, int philos_num)
{
	int		i;
	long	time_diff;

	i = 0;
	if (philos_num == 1)
		return ;
	while (!is_dead(philo[i]) && total_meals_check(philo[i]))
	{
		pthread_mutex_lock(&philo[i]->table->time_lock);
		time_diff = get_duration(&philo[i]->life_tv);
		if (time_diff - philo[i]->life > philo[i]->time_die)
		{
			pthread_mutex_unlock(&philo[i]->table->time_lock);
			display_log(philo[i], DIE);
			pthread_mutex_lock(&philo[i]->table->table_lock);
			philo[i]->table->dead_philo = TRUE;
			pthread_mutex_unlock(&philo[i]->table->table_lock);
			return ;
		}
		pthread_mutex_unlock(&philo[i]->table->time_lock);
		i++;
		if (i == philos_num)
			i = 0;
	}
	return ;
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
			pthread_create(&main.philo[main.i]->thread, NULL, \
						routine, main.philo[main.i]);
		inspecting_philos(main.philo, main.philos_num);
		while (++main.j < main.philos_num)
			pthread_join(main.philo[main.j]->thread, NULL);
		cleanup(main.philo, main.input, main.philos_num);
		return (0);
	}
	printf("Error\nInvalid number of arguments\n");
	return (1);
}
