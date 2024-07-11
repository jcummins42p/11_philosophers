/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:31:58 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/11 15:52:49 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_table *table)
{
	int		i;

	i = 0;
	table->philos = malloc(sizeof (t_philo *) * table->n_philos);
	while (i < table->n_philos)
	{
		table->philos[i] = malloc(sizeof(t_philo));
		pthread_mutex_init(&table->philos[i]->mutex, NULL);
		table->philos[i]->id = i;
		table->philos[i]->l_fork = NULL;
		table->philos[i]->r_fork = NULL;
		table->philos[i]->n_meals = 0;
		table->philos[i]->status = HUNGRY;
		table->philos[i]->table = table;
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
