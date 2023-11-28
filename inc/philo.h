/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 20:56:05 by alsaeed           #+#    #+#             */
/*   Updated: 2023/11/28 16:34:47 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <time.h>
# include <string.h>
# include <stdint.h>

/* Constants */
# define TAKE 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIE 5
# define FORK_LOCK 6
# define FORK_STAT 7
# define FORK_MASK 8

typedef struct s_table
{
	bool			dead_philo;
	bool			*fork_stat;
	int				*fork_mask;
	pthread_mutex_t	table_lock;
	pthread_mutex_t	*fork_lock;
}	t_table;

typedef struct s_philo
{
	int				id;
	int				meals;
	int				philos_num;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	long			life;
	struct timeval	life_tv;
	pthread_t		thread;
	t_table			*table;
}	t_philo;

int		parse_nonnum_arg(char **s);
char	**parse_args(int ac, char **av);
void	free_parse(char **arr);
void	free_array(char **array);
int		check_overflow(char **str, int ac);
int		ft_isspace_str(char *s);
int		ft_space_arg(char **s);
char	*ft_strjoin_sp(int ac, char **av);
int		ft_array_size(char **array);
char	**ft_get_array(int ac, char **av);
int		ft_atoi(char *num, int *error);
char	**ft_split(char *s, char c);
void	*ft_calloc(size_t count, size_t size);
void	fill_table(t_table *table, char **input);
void	init_philos(t_philo	**philo, char **input, int ac);
void	display_log(t_philo *philo, int stat);
bool	is_dead(t_philo *philo);
void	*single_philo(t_philo *philo);
long	get_duration(struct timeval *prev_time);
long	get_current_time(void);
bool	eating_time(t_philo *philo);
bool	sleeping_time(t_philo *philo);
bool	eat_noodles(t_philo *philo);
bool	check_greedy(t_philo *philo);
void	trigger_on(t_philo *philo, int flag);
void	trigger_mask(t_philo *philo);
void	trigger_off(t_philo *philo, int flag);
void	cleanup(t_philo **philos, char **input, int range);

#endif