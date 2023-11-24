/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:42:13 by alsaeed           #+#    #+#             */
/*   Updated: 2023/11/16 14:16:27 by alsaeed          ###   ########.fr       */
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

int		check_overflow(char **str, int ac)
{
	int	i;
	int error;
	int	dum;
	
	i = -1;
	error = 0;
	dum = 0;
	while (++i < ac - 1)
		dum = ft_atoi(str[i], &error);
	if (error == -1)
		return (1);
	return (0);
}

void	free_parse(char **arr)
{
	if (arr)
		free_array(arr);
	write(2, "Error: Invalid arguments\n", 25);
	exit (1);
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

char	**parse_args(int ac, char **av)
{
	char	*str;
	char	**str_arr;

	str_arr = NULL;
	if (ft_space_arg(av) == -1)
	{
		printf("Error\n");
		exit (1);
	}
	str = ft_strjoin_sp(ac, av);
	str_arr = ft_split(str, ' ');
	free (str);
	str = NULL;
	if (parse_nonnum_arg(str_arr) == -1 || check_overflow(str_arr, ac) == -1)
	{
		free_array(str_arr);
		printf("Error\n");
		exit (1);
	}
	return (str_arr);
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

int	ft_array_size(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}

char	**ft_get_array(int ac, char **av)
{
	char	*str;
	char	**array;

	str = NULL;
	array = NULL;
	str = ft_strjoin_sp(ac, av);
	array = ft_split(str, ' ');
	free (str);
	str = NULL;
	if (ft_array_size(array) != 5)
	{
		free_array(array);
		exit (0);
	}
	return (array);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*memory;
	
	if (count != 0 && size != 0 && count > SIZE_MAX / size)
		return (NULL);
	memory = malloc(count * size);
	if (memory == NULL)
		return (NULL);
	memset(memory, 0, count * size);
	return (memory);
}
