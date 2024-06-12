/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:08:57 by jcummins          #+#    #+#             */
/*   Updated: 2024/06/12 19:06:48 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_exit(int errcode)
{
	if (errcode == TIME_FAIL)
		printf("Gettimeofday failed\n");
	exit (errcode);
}

void	print_errcode(int errcode, int argc)
{
	if (errcode == N_ARGS)
		printf(KRED "Exit: bad number of arguments (%d)\n" KDEF, argc - 1);
	if (errcode == BAD_ARGS)
		printf(KRED "Exit: due to bad argument\n" KDEF);
	exit (errcode);
}

void	print_error(t_table *table, int err)
{
	if (err)
		printf(KRED "Input Error:\n");
	if (err & 1)
		printf(KRED "\tInvalid number of philosophers\n");
	else
		printf(KGRN "\tValid number of philosophers: %ld\n", table->n_philos);
	if ((err >> 1) & 1)
		printf(KRED "\tInvalid time to die\n");
	else
		printf(KGRN "\tValid time to die: %ld\n", table->time_to_die);
	if ((err >> 2) & 1)
		printf(KRED "\tInvalid time to eat argument\n");
	else
		printf(KGRN "\tValid time to eat: %ld\n", table->time_to_eat);
	if ((err >> 3) & 1)
		printf(KRED "\tInvalid time to sleep argument\n");
	else
		printf(KGRN "\tValid time to sleep: %ld\n", table->time_to_sleep);
	if ((err >> 4) & 1)
		printf(KRED "\tInvalid meal limit argument\n" KDEF);
	else
		printf(KGRN "\tValid meal limit: %d\n" KDEF, table->n_limit_meals);
}
