/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:08:57 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/27 18:10:31 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(t_table *table, int err)
{
	if (err)
		printf("Input Error:\n");
	if (err & 1)
		printf("\tInvalid number of philosophers\n");
	else
		printf("\tValid number of philosophers: %ld\n", table->n_philos);
	if ((err >> 1) & 1)
		printf("\tInvalid time to die\n");
	else
		printf("\tValid time to die: %ld\n", table->time_to_die);
	if ((err >> 2) & 1)
		printf("\tInvalid time to eat argument\n");
	else
		printf("\tValid time to eat: %ld\n", table->time_to_eat);
	if ((err >> 3) & 1)
		printf("\tInvalid time to sleep argument\n");
	else
		printf("\tValid time to sleep: %ld\n", table->time_to_sleep);
	if ((err >> 4) & 1)
		printf("\tInvalid meal limit argument\n");
	else
		printf("\tValid meal limit: %ld\n", table->n_limit_meals);
}

int	check_input(t_table *table)
{
	int	invalid;

	invalid = 0;
	if (table->n_philos < 1)
		invalid += 1;
	if (table->time_to_die < 1)
		invalid += 2;
	if (table->time_to_eat < 0)
		invalid += 4;
	if (table->time_to_sleep < 0)
		invalid += 8;
	if (table->n_limit_meals < 0)
		invalid += 16;
	if (invalid)
		print_error(table, invalid);
	return (invalid);
}
