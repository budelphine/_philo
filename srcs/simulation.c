/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budelphi <budelphi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 16:21:43 by budelphi          #+#    #+#             */
/*   Updated: 2021/06/12 15:52:47 by budelphi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*supervision(void *data)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)data;
	while (1)
	{
		i = -1;
		while (++i < philo->table->philo_num)
		{
			if (philo->table->full_philo_counter == philo->table->philo_num \
				&& philo->table->max_dining_counter)
			{
				pthread_mutex_lock(philo->table->dead_mutex);
				return (NULL);
			}
			if (philo[i].table->time_to_die < \
				(get_time() - philo[i].last_eat_time))
			{
				make_message(&philo[i], DEAD);
				pthread_mutex_lock(philo->table->dead_mutex);
				return (NULL);
			}
		}
	}
	return (NULL);
}

static void	handle_fork(t_philo *philo, pthread_mutex_t *first_fork, \
		pthread_mutex_t *second_fork)
{
	pthread_mutex_lock(first_fork);
	make_message(philo, TAKEN_FORK);
	pthread_mutex_lock(second_fork);
	make_message(philo, TAKEN_FORK);
}

int	philo_eat(t_philo *philo)
{
	if (philo->id % 2 != 0)
		handle_fork(philo, &philo->forks[philo->left_fork], \
			&philo->forks[philo->right_fork]);
	else
		handle_fork(philo, &philo->forks[philo->right_fork], \
			&philo->forks[philo->left_fork]);
	pthread_mutex_lock(philo->table->dead_mutex);
	pthread_mutex_unlock(philo->table->dead_mutex);
	make_message(philo, EAT);
	philo->last_eat_time = get_time();
	ft_wait(philo->table->time_to_eat);
	philo->dining_counter++;
	if (philo->table->max_dining_counter == philo->dining_counter)
		philo->table->full_philo_counter++;
	pthread_mutex_unlock(&philo->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->forks[philo->left_fork]);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	make_message(philo, SLEEP);
	ft_wait(philo->table->time_to_sleep);
	return (0);
}

int	philo_think(t_philo *philo)
{
	make_message(philo, THINK);
	return (0);
}
