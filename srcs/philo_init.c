/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budelphi <budelphi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 16:06:41 by budelphi          #+#    #+#             */
/*   Updated: 2021/06/12 15:54:27 by budelphi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

pthread_mutex_t	*init_forks(t_table *table)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
		* table->philo_num);
	if (!forks)
		return ((pthread_mutex_t *)ft_print_error(MALLOC_ERROR, 0));
	i = -1;
	while (++i < table->philo_num)
		pthread_mutex_init(&forks[i], NULL);
	return (forks);
}

t_philo	*init_entry_mutex(t_philo *philo)
{
	pthread_mutex_t	*dead_mutex;

	if (!philo)
		return (NULL);
	dead_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!dead_mutex)
		return ((t_philo *)ft_print_error(MALLOC_ERROR, 0));
	pthread_mutex_init(dead_mutex, NULL);
	philo->table->dead_mutex = dead_mutex;
	return (philo);
}

t_philo	*init_philo(t_table	*table, pthread_mutex_t *forks)
{
	t_philo	*philo;
	int		i;

	if (!table || !forks)
		return (NULL);
	philo = (t_philo *)malloc(sizeof(t_philo) * table->philo_num);
	if (!philo)
		return ((t_philo *)ft_print_error(MALLOC_ERROR, 0));
	i = -1;
	while (++i < table->philo_num)
	{
		philo[i].id = i;
		philo[i].left_fork = i;
		philo[i].right_fork = (i + 1) % table->philo_num;
		philo[i].dining_counter = 0;
		philo[i].table = table;
		philo[i].forks = forks;
	}
	return (philo);
}
