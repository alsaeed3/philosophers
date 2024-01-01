/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:24:45 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/01 18:33:36 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

char	**ft_get_array(int ac, char **av, t_bool *error)
{
	char	*str;
	char	**array;

	str = NULL;
	array = NULL;
	str = ft_strjoin_sp(ac, av, error);
	array = ft_split(str, ' ');
	free (str);
	str = NULL;
	if (ft_array_size(array) != 5)
	{
		free_array(array);
		*error = TRUE;
	}
	return (array);
}

void	cleanup(t_philo **philos, char **input, int range)
{
	int	i;

	free_array(input);
	i = -1;
	while (++i < range)
		pthread_mutex_destroy(&philos[i]->table->fork_lock[i]);
	pthread_mutex_destroy(&(*philos)->table->print_lock);
	pthread_mutex_destroy(&(*philos)->table->time_lock);
	pthread_mutex_destroy(&(*philos)->table->table_lock);
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

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		if (!array[i])
			return ;
		free (array[i]);
		array[i] = NULL;
		i++;
	}
	if (array[i])
	{
		free (array[i]);
		array[i] = NULL;
	}
	if (array)
	{
		free (array);
		array = NULL;
	}
}

void	free_parse(char **arr)
{
	if (arr)
		free_array(arr);
	printf("Error\nInvalid arguments\n");
}
