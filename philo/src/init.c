/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:31:58 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/28 12:55:09 by jcummins         ###   ########.fr       */
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
		philo->state = HUNGRY;
		philo->table = table;
		table->philos[i] = philo;
		i++;
	}
	return (0);
}
