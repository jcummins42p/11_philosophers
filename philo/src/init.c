/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:31:58 by jcummins          #+#    #+#             */
/*   Updated: 2024/06/11 20:05:43 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = NULL;
	table->philos = malloc(sizeof (t_philo *) * table->n_philos);
	while (i < table->n_philos)
	{
		philo = malloc(sizeof(t_philo));
		philo->id = i;
		philo->l_fork = NULL;
		philo->r_fork = NULL;
		philo->n_meals = 0;
		philo->status = HUNGRY;
		philo->full = false;
		philo->table = table;
		table->philos[i] = philo;
		i++;
	}
	return (0);
}

int	init_forks(t_table *table)
{
	int		i;
	t_fork	*fork;

	i = 0;
	fork = NULL;
	table->forks = malloc(sizeof (t_fork *) * table->n_philos);
	while (i < table->n_philos)
	{
		fork = malloc(sizeof(t_philo));
		fork->id = i;
		pthread_mutex_init(&fork->mutex, NULL);
		table->forks[i] = fork;
		i++;
	}
	return (0);
}
