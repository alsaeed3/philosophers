/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:23:47 by alsaeed           #+#    #+#             */
/*   Updated: 2023/12/30 17:24:02 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_bool	ft_is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (TRUE);
	return (FALSE);
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
	i = 0;
	k = 0;
	while (++i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			check_digit_after_space(av, i, j, error);
			str[k++] = av[i][j++];
		}
		if (av[i + 1] != NULL)
			str[k++] = ' ';
	}
	str[k] = '\0';
	return (str);
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
