/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:08:57 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/28 12:05:39 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_errcode(int errcode, int argc)
{
	if (errcode == N_ARGS)
		printf("Program exit due to bad number of arguments (%d)\n", argc - 1);
	if (errcode == BAD_ARGS)
		printf("Program exit due to bad argument\n");
}

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
