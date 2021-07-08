/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budelphi <budelphi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 19:55:20 by budelphi          #+#    #+#             */
/*   Updated: 2021/06/12 16:50:01 by budelphi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_destroy_mutex(char *err_message, t_philo *philo)
{
	pthread_mutex_t		*forks;
	int					i;

	if (err_message)
		ft_print_error(SMTH_WENT_WRONG, 0);
	forks = philo->forks;
	i = -1;
	while (++i < philo->table->philo_num)
		pthread_mutex_destroy(&forks[i]);
	pthread_mutex_destroy(philo->table->dead_mutex);
	return (1);
}

void	*ft_print_error(char *err_message, void *ret_value)
{
	write(2, err_message, ft_strlen(err_message));
	return (ret_value);
}

time_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((time_t)(((tv.tv_sec) * 1000) + ((tv.tv_usec) / 1000)));
}

void	*make_message(t_philo *philo, char *message)
{
	long			current_time;

	pthread_mutex_lock(philo->table->dead_mutex);
	pthread_mutex_unlock(philo->table->dead_mutex);
	current_time = get_time() - philo->start_sim_time;
	printf("%-8ld -  Philo %2d - %s\n", current_time, philo->id + 1, message);
	return (NULL);
}

void	ft_wait(time_t time_to_usleep_ms)
{
	time_t	start;
	time_t	stop;
	time_t	diff;

	start = get_time();
	stop = get_time();
	diff = stop - start;
	while (diff < time_to_usleep_ms)
	{
		stop = get_time();
		diff = stop - start;
		usleep(10);
	}
}
