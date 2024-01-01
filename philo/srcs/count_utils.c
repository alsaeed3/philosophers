/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:42:13 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/01 18:45:48 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	ft_atoi(char *num, t_bool *error)
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
			*error = TRUE;
		i++;
	}
	if (num[i] == '+')
		*error = TRUE;
	while (num[i] >= '0' && num[i] <= '9')
	{
		res = res * 10 + num[i] - 48;
		if (res > 2147483647)
			*error = TRUE;
		i++;
	}
	if (!res)
		*error = TRUE;
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

int	ft_count_words(char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s != c && (*(s + 1) == c || *(s + 1) == '\0'))
			count++;
		s++;
	}
	return (count);
}

int	ft_wordlen(char *s, char c)
{
	int	len;

	len = 0;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

int	char_no(char **av)
{
	int		i;
	int		j;
	int		count;

	i = 1;
	count = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			count++;
			j++;
		}
		i++;
	}
	return (count);
}
