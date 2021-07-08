/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budelphi <budelphi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 14:31:40 by budelphi          #+#    #+#             */
/*   Updated: 2021/06/12 16:49:43 by budelphi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*simulation(void *data)
{
	t_philo			*philo;

	philo = (t_philo *)data;
	philo->start_sim_time = get_time();
	philo->last_eat_time = philo->start_sim_time;
	while (1)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

int	start_simulation(t_philo *philo)
{
	pthread_t	*philo_threads;
	pthread_t	*philo_observer;
	int			philo_num;
	int			i;

	philo_num = philo[0].table->philo_num;
	philo_observer = (pthread_t *)malloc(sizeof(pthread_t));
	philo_threads = (pthread_t *)malloc(sizeof(pthread_t) * philo_num);
	if (!philo_threads || !philo_observer)
		return ((int)ft_print_error(MALLOC_ERROR, 0));
	i = -1;
	while (++i < philo_num)
	{
		if (pthread_create(&philo_threads[i], NULL, simulation, &philo[i]) != 0)
			return (ft_destroy_mutex(SMTH_WENT_WRONG, philo));
		pthread_detach(philo_threads[i]);
	}
	usleep(50);
	if (pthread_create(philo_observer, NULL, supervision, philo) != 0)
		return (ft_destroy_mutex(SMTH_WENT_WRONG, philo));
	pthread_join(*philo_observer, NULL);
	return (ft_destroy_mutex(NULL, philo));
}

int	dining_philo(int ac, char **av)
{
	t_table				*table;
	t_philo				*philo;
	pthread_mutex_t		*forks;

	table = philo_parser(ac, av);
	forks = init_forks(table);
	philo = init_philo(table, forks);
	philo = init_entry_mutex(philo);
	if (!philo)
		return (0);
	start_simulation(philo);
	return (1);
}

int	main(int ac, char **av)
{
	int	res;

	if (ac < 5 || ac > 6)
		return ((int)ft_print_error(WRONG_NUM_OF_ARGUMENT, 0));
	res = dining_philo(ac, av);
	return (res);
}
