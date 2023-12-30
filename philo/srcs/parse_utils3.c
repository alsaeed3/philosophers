/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:42:13 by alsaeed           #+#    #+#             */
/*   Updated: 2023/12/30 17:05:43 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_bool	parse_nonnum_arg(char **s)
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
				return (TRUE);
			if ((s[j][i] == '+' || s[j][i] == '-' \
			|| (s[j][i] >= '0' && s[j][i] <= '9')) \
			&& (s[j][i + 1] == '+' || s[j][i + 1] == '-'))
				return (TRUE);
			if ((s[j][i] == '+' || s[j][i] == '-') \
			&& (s[j][i + 1] == ' ' || s[j][i + 1] == '\0'))
				return (TRUE);
			i++;
		}
		j++;
	}
	return (FALSE);
}

void	get_array(int ac, char **av, char ***str_arr, t_bool *error)
{
	char	*str;

	str = NULL;
	str = ft_strjoin_sp(ac, av, error);
	*str_arr = ft_split(str, ' ');
	free (str);
	if (parse_nonnum_arg(*str_arr))
	{
		free_parse(*str_arr);
		*error = TRUE;
	}
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

t_bool	ft_space_arg(char **s, t_bool *error)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_isspace_str(s[i]))
		{
			*error = TRUE;
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
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
