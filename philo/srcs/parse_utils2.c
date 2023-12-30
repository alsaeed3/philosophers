/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:20:55 by alsaeed           #+#    #+#             */
/*   Updated: 2023/12/30 17:23:01 by alsaeed          ###   ########.fr       */
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
	if (ft_space_arg(av, error))
	{
		printf("Error\nSpace-only or null argument\n");
		return (NULL);
	}
	str = ft_strjoin_sp(ac, av, error);
	if (*error)
	{
		printf("Error\nSpace between Numbers on the same Argument\n");
		return (free(str), NULL);
	}
	str_arr = ft_split(str, ' ');
	i = -1;
	free (str);
	str = NULL;
	if (ft_check_array(str_arr, ac, error))
		return (NULL);
	return (str_arr);
}

t_bool	ft_check_array(char **str_arr, int ac, t_bool *error)
{
	if (parse_nonnum_arg(str_arr) || check_overflow(str_arr, ac) \
		|| !ft_atoi(str_arr[0], error) || !ft_atoi(str_arr[1], error) \
		|| !ft_atoi(str_arr[2], error) || !ft_atoi(str_arr[3], error) \
		|| (ac == 6 && !ft_atoi(str_arr[4], error)))
	{
		printf("Error\nNon-num/Over-flow/Zero/Negative argument\n");
		*error = TRUE;
		free_array(str_arr);
		return (TRUE);
	}
	return (FALSE);
}

int	ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
