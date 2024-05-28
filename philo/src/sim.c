/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:43:20 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/28 14:03:38 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	run_sim(t_table *table)
{
	(void) table;
}

int	start_sim(t_table *table)
{
	int	i;

	i = 0;
	if (table->n_limit_meals == 0)
		return 0;
	else if (table->n_philos == 1)
		return 0;
	else
	{
		while (i < table->n_philos)
		{
			if (table->philos[i]->state == THINKING)
				printf("Philosopher %d is thinking\n", table->philos[i]->id);
			else if (table->philos[i]->state == HUNGRY)
				printf(KYEL "Philosopher %d is hungry\n", table->philos[i]->id);
			else if (table->philos[i]->state == EATING)
				printf(KGRN "Philosopher %d is eating\n", table->philos[i]->id);
			else if (table->philos[i]->state == DEAD)
				printf(KRED "Philosopher %d is dead\n", table->philos[i]->id);
			printf(KDEF);
			i++;
		}
	}
	return 0;
}
