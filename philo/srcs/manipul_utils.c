/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipul_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:53:09 by alsaeed           #+#    #+#             */
/*   Updated: 2024/01/02 14:42:04 by alsaeed          ###   ########.fr       */
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

static char	*ft_wordcpy(char *dst, char *src, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	**ft_split(char *s, char c)
{
	char	**array;
	int		i;
	int		len;

	if (!s)
		return (NULL);
	array = ft_calloc(sizeof(char *), (ft_count_words(s, c) + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			len = ft_wordlen(s, c);
			array[i] = ft_calloc(sizeof(char), (len + 1));
			if (!array[i])
				return (NULL);
			ft_wordcpy(array[i++], s, len);
			s = s + len;
		}
	}
	return (array[i] = NULL, array);
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
