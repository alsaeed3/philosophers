/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 20:56:15 by alsaeed           #+#    #+#             */
/*   Updated: 2023/11/26 19:09:12 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	eat_noodles(t_philo *philo)
{
	trigger_on(philo, FORK_STAT);
	trigger_on(philo, FORK_MASK);
	trigger_on(philo, FORK_LOCK);
	philo->life = get_duration(&philo->life_tv);
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

int	check_eating(t_philo *philo)
{
	if ((philo->id % philo->table->philos_num) \
			&& !philo->table->fork_stat[philo->id - 1] \
			&& !philo->table->fork_stat[philo->id] \
			&& philo->meals && mask_fork(philo))
	{
		if (eat_noodles(philo))
			return (1);
	}
	else if (!(philo->id % philo->table->philos_num) \
			&& !philo->table->fork_stat[philo->id - 1] \
			&& !philo->table->fork_stat[0] && philo->meals \
			&& mask_fork(philo))
	{
		if (eat_noodles(philo))
			return (1);
	}
	return (0);
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
		if (check_eating(philo))
			return (NULL);
		trigger_on(philo, FORK_LOCK);
		usleep(50);
	}
	return (NULL);
}

int	main(int ac, char **av)
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
