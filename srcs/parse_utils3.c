/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:42:13 by alsaeed           #+#    #+#             */
/*   Updated: 2023/11/26 18:54:09 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	parse_nonnum_arg(char **s)
{
	int	j;
	int	i;

	j = 0;
	while (s[j])
	{
		i = 0;
		while (s[j][i])
		{
			if (s[j][i] != ' ' && !(s[j][i] == '-' || s[j][i] == '+') \
			&& !(s[j][i] >= '0' && s[j][i] <= '9'))
				return (-1);
			if ((s[j][i] == '+' || s[j][i] == '-' \
			|| (s[j][i] >= '0' && s[j][i] <= '9')) \
			&& (s[j][i + 1] == '+' || s[j][i + 1] == '-'))
				return (-1);
			if ((s[j][i] == '+' || s[j][i] == '-') \
			&& (s[j][i + 1] == ' ' || s[j][i + 1] == '\0'))
				return (-1);
			i++;
		}
		j++;
	}
	return (0);
}

void	get_array(int ac, char **av, char ***str_arr)
{
	char	*str;

	str = NULL;
	str = ft_strjoin_sp(ac, av);
	*str_arr = ft_split(str, ' ');
	free (str);
	if (parse_nonnum_arg(*str_arr) == -1)
		free_parse(*str_arr);
}

int	ft_isspace_str(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] != ' ')
			return (0);
		i++;
	}
	return (-1);
}

int	ft_space_arg(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_isspace_str(s[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
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
