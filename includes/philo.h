/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budelphi <budelphi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 19:49:57 by budelphi          #+#    #+#             */
/*   Updated: 2021/06/12 16:50:37 by budelphi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

# define	ONE_MS	1000
# define	ONE_S	1000000

# define	WRONG_NUM_OF_ARGUMENT	"Wrong number of argument\n"
# define	MALLOC_ERROR			"Malloc error...\n"

# define	INCORRECT_PARAM		"Incorrect param\n"
# define	NON_NUMERIC_PARAM	"The non-numeric value of the parameter\n"
# define	LESS_ZERO_PARAM		"The parameter is less than or equal to zero\n"
# define	LESS_60_PARAM		"The parameter time_to is less than 60\n"
# define	MORE_THAN200_PHILO	"Number of Philosophers should be less <= 200\n"

# define	SMTH_WENT_WRONG		"Something went wrong, please try again...\n"

# define	TAKEN_FORK			"has taken a fork"
# define	EAT					"is eating"
# define	SLEEP				"is sleeping"
# define	THINK				"is thinking"
# define	DEAD				"died"
# define	PHILO_IS_FULL		"all Philo is full"

typedef struct s_table
{
	int					philo_num;
	int					philo_died;
	time_t				time_to_die;
	time_t				time_to_eat;
	time_t				time_to_sleep;
	int					max_dining_counter;
	int					full_philo_counter;
	pthread_mutex_t		*dead_mutex;
}						t_table;

typedef struct s_philo
{
	int					id;
	int					left_fork;
	int					right_fork;
	int					dining_counter;
	time_t				start_sim_time;
	time_t				last_eat_time;
	t_table				*table;
	pthread_mutex_t		*forks;
}						t_philo;

void				*supervision(void *data);
void				*simulation(void *data);
int					philo_think(t_philo *philo);
int					philo_sleep(t_philo *philo);
int					philo_eat(t_philo *philo);

t_philo				*init_entry_mutex(t_philo *philo);
pthread_mutex_t		*init_forks(t_table *table);
t_philo				*init_philo(t_table	*table, pthread_mutex_t *forks);
t_table				*philo_parser(int ac, char **av);

int					ft_destroy_mutex(char *err_message, t_philo *philo);
void				*ft_print_error(char *err_message, void *ret_value);
void				*make_message(t_philo *philo, char *message);
void				ft_wait(time_t time_to_usleep_ms);
time_t				get_time(void);

int					ft_atoi(const char *str);
size_t				ft_strlen(const char *str);
int					ft_putstr_fd(char *str, int fd);
int					ft_isdigit(int c);

#endif
