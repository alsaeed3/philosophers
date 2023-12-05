/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:20:55 by alsaeed           #+#    #+#             */
/*   Updated: 2023/12/04 16:23:33 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_overflow(char **str, int ac)
{
	int	i;
	int	error;

	i = -1;
	error = 0;
	while (++i < ac - 1)
		ft_atoi(str[i], &error);
	if (error == -1)
		return (1);
	return (0);
}

void	free_parse(char **arr)
{
	if (arr)
		free_array(arr);
	printf("Error\nInvalid arguments\n");
	exit (1);
}

char	**parse_args(int ac, char **av)
{
	char	*str;
	char	**str_arr;
	int		i;

	i = 0;
	str_arr = NULL;
	if (ft_space_arg(av) == -1)
	{
		printf("Error\nSpace-only argument\n");
		exit (1);
	}
	str = ft_strjoin_sp(ac, av);
	str_arr = ft_split(str, ' ');
	free (str);
	str = NULL;
	if (parse_nonnum_arg(str_arr) == -1 || check_overflow(str_arr, ac) == -1 \
		|| !ft_atoi(str_arr[0], &i) || !ft_atoi(str_arr[1], &i) \
		|| !ft_atoi(str_arr[2], &i) || !ft_atoi(str_arr[3], &i) || i == -1)
	{
		printf("Error\nNon-num/Over-flow/Zero/Negative argument\n");
		free_array(str_arr);
		exit (1);
	}
	return (str_arr);
}

static int	char_no(char **av)
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

char	*ft_strjoin_sp(int ac, char **av)
{
	char	*str;
	int		size;
	int		i;
	int		j;
	int		k;

	size = char_no(av) + ac;
	str = ft_calloc(sizeof(char), size);
	if (!str)
		exit (1);
	i = 1;
	k = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
			str[k++] = av[i][j++];
		if (av[i + 1] != NULL)
			str[k++] = ' ';
		i++;
	}
	str[k] = '\0';
	return (str);
}
