/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 18:39:18 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/01 18:47:14 by alsaeed          ###   ########.fr       */
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
