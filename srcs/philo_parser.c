/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budelphi <budelphi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 14:32:37 by budelphi          #+#    #+#             */
/*   Updated: 2021/06/12 15:52:37 by budelphi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_check_valid(t_table *table, int ac)
{
	if (ac == 6 && table->max_dining_counter <= 0)
		return ((int)ft_print_error(LESS_ZERO_PARAM, 0));
	if (table->philo_num > 200)
		return ((int)ft_print_error(MORE_THAN200_PHILO, 0));
	if (table->time_to_die < 60 || table->time_to_eat < 60 \
		|| table->time_to_sleep < 60)
		return ((int)ft_print_error(LESS_60_PARAM, 0));
	return (1);
}

static int	ft_parse_elem(char *num_args)
{
	int	i;
	int	res;

	if (ft_strlen(num_args) > 9)
		return ((int)ft_print_error(INCORRECT_PARAM, 0));
	i = -1;
	while (num_args[++i])
	{
		if (!ft_isdigit(num_args[i]))
			return ((int)ft_print_error(NON_NUMERIC_PARAM, 0));
	}
	res = ft_atoi(num_args);
	if (res <= 0)
		return ((int)ft_print_error(LESS_ZERO_PARAM, 0));
	return (res);
}

t_table	*philo_parser(int ac, char **av)
{
	t_table	*table;

	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return ((t_table *)ft_print_error(MALLOC_ERROR, 0));
	table->philo_died = 0;
	table->full_philo_counter = 0;
	table->max_dining_counter = 0;
	table->philo_num = ft_parse_elem(av[1]);
	table->time_to_die = ft_parse_elem(av[2]);
	table->time_to_eat = ft_parse_elem(av[3]);
	table->time_to_sleep = ft_parse_elem(av[4]);
	if (ac == 6)
		table->max_dining_counter = ft_parse_elem(av[5]);
	if (!ft_check_valid(table, ac))
		return ((t_table *)ft_print_error(SMTH_WENT_WRONG, 0));
	return (table);
}
