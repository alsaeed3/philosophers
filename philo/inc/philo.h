/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 20:56:05 by alsaeed           #+#    #+#             */
/*   Updated: 2023/12/30 18:21:49 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
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

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_table
{
	t_bool			dead_philo;
	int				total_meals;
	t_bool			*fork_stat;
	int				*fork_mask;
	pthread_mutex_t	table_lock;
	pthread_mutex_t	*fork_lock;
}	t_table;

typedef struct s_philo
{
	int				id;
	int				meals;
	int				philos_num;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	long			life;
	struct timeval	life_tv;
	pthread_t		thread;
	t_table			*table;
}	t_philo;

typedef struct s_main
{
	t_philo		**philo;
	char		**input;
	int			i;
	int			j;
	int			philos_num;
	t_bool		error;
}	t_main;

void		fill_main(t_main *main);
t_bool		parse_nonnum_arg(char **s);
char		**parse_args(int ac, char **av, t_bool *error);
void		free_parse(char **arr);
void		free_array(char **array);
t_bool		check_overflow(char **str, int ac);
t_bool		ft_isspace_str(char *s);
t_bool		ft_space_arg(char **s, t_bool *error);
char		*ft_strjoin_sp(int ac, char **av, t_bool *error);
int			ft_array_size(char **array);
char		**ft_get_array(int ac, char **av, t_bool *error);
long		ft_atoi(char *num, t_bool *error);
char		**ft_split(char *s, char c);
t_bool		ft_check_array(char **str_arr, int ac, t_bool *error);
void		check_digit_after_space(char **av, int i, int j, t_bool *error);
t_bool		ft_is_digit(char c);
t_bool		ft_check_after_space(char *str, int i, int len_str);
int			ft_strlen(char *str);
void		*ft_calloc(size_t count, size_t size);
t_table		*fill_table(int philos_num);
void		init_philos(t_philo	**philo, char **input, int philos_num, \
			t_bool *error);
void		display_log(t_philo *philo, int stat);
t_bool		is_dead(t_philo *philo);
void		*single_philo(t_philo *philo);
long		get_duration(struct timeval *prev_time);
long		get_current_time(void);
t_bool		eating_time(t_philo *philo);
t_bool		sleeping_time(t_philo *philo);
t_bool		sleep_bro(t_philo *philo);
t_bool		eat_noodles(t_philo *philo);
t_bool		check_greedy(t_philo *philo);
void		trigger_off(t_philo *philo, int flag);
void		trigger_mask(t_philo *philo);
void		trigger_on(t_philo *philo, int flag);
void		cleanup(t_philo **philos, char **input, int range);

#endif