/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:31:58 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/15 18:00:14 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_table(t_table *table, char *argv[])
{
	table->n_philos = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * MSEC;
	table->time_to_eat = ft_atol(argv[3]) * MSEC;
	table->time_to_sleep = ft_atol(argv[4]) * MSEC;
	if (argv[5])
		table->n_limit_meals = ft_atol(argv[5]);
	else
		table->n_limit_meals = 0;
	table->n_hungry_philos = table->n_philos;
	gettimeofday(&table->start_time, NULL);
	table->sim_status = WAITING;
	table->forks = NULL;
	table->philos = NULL;
	table->monitor_id = 0;
	pthread_mutex_init(&table->mutex, NULL);
	return (0);
}

int	init_philos(t_table *table)
{
	int		i;

	i = 0;
	table->philos = malloc(sizeof (t_philo *) * table->n_philos);
	while (i < table->n_philos)
	{
		table->philos[i] = malloc(sizeof(t_philo));
		table->philos[i]->id = i;
		pthread_mutex_init(&table->philos[i]->mutex, NULL);
		table->philos[i]->status = HUNGRY;
		table->philos[i]->full = false;
		table->philos[i]->l_fork = NULL;
		table->philos[i]->r_fork = NULL;
		table->philos[i]->n_meals = 0;
		table->philos[i]->table = table;
		gettimeofday(&table->philos[i]->start_time, NULL);
		table->philos[i]->last_meal_time = 0;
		i++;
	}
	return (0);
}

int	init_forks(t_table *table)
{
	int		i;

	table->forks = malloc(sizeof (t_fork *) * table->n_philos);
	i = 0;
	while (i < table->n_philos)
	{
		table->forks[i] = malloc(sizeof(t_philo));
		table->forks[i]->id = i;
		pthread_mutex_init(&table->forks[i]->mutex, NULL);
		i++;
	}
	return (0);
}
