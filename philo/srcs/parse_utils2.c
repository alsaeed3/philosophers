/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:20:55 by alsaeed           #+#    #+#             */
/*   Updated: 2023/12/29 16:23:36 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_bool	check_overflow(char **str, int ac)
{
	int		i;
	t_bool	error;

	i = -1;
	error = FALSE;
	while (++i < ac - 1)
		ft_atoi(str[i], &error);
	if (error)
		return (TRUE);
	return (FALSE);
}

void	free_parse(char **arr)
{
	if (arr)
		free_array(arr);
	printf("Error\nInvalid arguments\n");
}

char	**parse_args(int ac, char **av, t_bool *error)
{
	char	*str;
	char	**str_arr;
	int		i;

	i = 0;
	str_arr = NULL;
	if (ft_space_arg(av))
	{
		printf("Error\nSpace-only or null argument\n");
		*error = TRUE;
		return (NULL);
	}
	str = ft_strjoin_sp(ac, av, error);
	str_arr = ft_split(str, ' ');
	i = -1;
	while ((ac == 5 && ++i < ac - 1) || (ac == 6 && ++i < ac - 1))
		if (str_arr[i][0] == '0' && str_arr[i][1] != '\0')
			*error = TRUE;
	free (str);
	str = NULL;
	if (parse_nonnum_arg(str_arr) || check_overflow(str_arr, ac) \
		|| !ft_atoi(str_arr[0], error) || !ft_atoi(str_arr[1], error) \
		|| !ft_atoi(str_arr[2], error) || !ft_atoi(str_arr[3], error) \
		|| (ac == 6 && !ft_atoi(str_arr[4], error)))
	{
		printf("Error\nNon-num/Over-flow/Zero/Negative argument\n");
		free_array(str_arr);
		*error = TRUE;
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

char	*ft_strjoin_sp(int ac, char **av, t_bool *error)
{
	char	*str;
	int		size;
	int		i;
	int		j;
	int		k;

	size = char_no(av) + ac;
	str = ft_calloc(sizeof(char), size);
	if (!str)
		*error = TRUE;
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
