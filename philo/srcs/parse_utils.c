/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 18:39:18 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/02 13:50:25 by alsaeed          ###   ########.fr       */
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

char	**parse_args(int ac, char **av, t_bool *error)
{
	char	*str;
	char	**str_arr;

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
	free (str);
	str = NULL;
	if (ft_check_array(str_arr, ac, error))
		return (NULL);
	return (str_arr);
}
