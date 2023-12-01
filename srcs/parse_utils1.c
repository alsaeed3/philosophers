/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:24:45 by alsaeed           #+#    #+#             */
/*   Updated: 2023/11/28 20:38:27 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_atoi(char *num, int *error)
{
	int		i;
	long	res;

	res = 0;
	i = 0;
	while (num[i] == ' ' || (num[i] >= '\t' && num[i] <= '\r'))
		i++;
	if (num[i] == '-' || num[i] == '+')
	{
		if (num[i] == '-')
			*error = -1;
		i++;
	}
	if (num[i] == '+')
		*error = -1;
	while (num[i] >= '0' && num[i] <= '9')
	{
		res = res * 10 + num[i] - 48;
		if (res > 2147483647)
			*error = -1;
		i++;
	}
	return (res);
}

int	ft_array_size(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}

char	**ft_get_array(int ac, char **av)
{
	char	*str;
	char	**array;

	str = NULL;
	array = NULL;
	str = ft_strjoin_sp(ac, av);
	array = ft_split(str, ' ');
	free (str);
	str = NULL;
	if (ft_array_size(array) != 5)
	{
		free_array(array);
		exit (0);
	}
	return (array);
}

void	display_log(t_philo *philo, int stat)
{
	pthread_mutex_lock(&philo->table->table_lock);
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
	pthread_mutex_unlock(&philo->table->table_lock);
}

void	cleanup(t_philo **philos, char **input, int range)
{
	int	i;

	free_array(input);
	i = -1;
	while (++i < range)
		pthread_mutex_destroy(&philos[i]->table->fork_lock[i]);
	pthread_mutex_destroy(&(*philos)->table->table_lock);
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
