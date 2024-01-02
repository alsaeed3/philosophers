/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:23:47 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/02 13:50:29 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_bool	ft_is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (TRUE);
	return (FALSE);
}

void	check_digit_after_space(char **av, int i, int j, t_bool *error)
{
	if (ft_is_digit(av[i][j]) && av[i][j + 1] == ' ')
	{
		while (av[i][++j] == ' ')
			;
		if (ft_is_digit(av[i][j]))
			*error = TRUE;
	}
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

t_bool	ft_isspace_str(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] != ' ')
			return (FALSE);
		i++;
	}
	return (TRUE);
}
