/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:11:30 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/11 17:57:58 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_valid_input(t_table *table)
{
	usleep(100000);
	printf(KGRN "Input valid:\n");
	printf("\t✅ Number of philosophers is %ld\n", table->n_philos);
	printf("\t✅ Time to die is %ld ms\n", table->time_to_die / MSEC);
	printf("\t✅ Time to eat is %ld ms\n", table->time_to_eat / MSEC);
	printf("\t✅ Time to sleep is %ld ms\n", table->time_to_sleep / MSEC);
	if (table->n_limit_meals)
		printf("\t✅ Meal limit is %d\n", table->n_limit_meals);
	else
		printf("\t✅ No meal limit set\n");
	printf(KDEF);
	usleep(3000000);
}

int	check_input(t_table *table)
{
	table->validity = 0;
	if (table->n_philos < 1)
		table->validity += 1;
	if (table->time_to_die < 1)
		table->validity += 2;
	if (table->time_to_eat < 0)
		table->validity += 4;
	if (table->time_to_sleep < 0)
		table->validity += 8;
	if (table->n_limit_meals < 0)
		table->validity += 16;
	if (table->validity)
		print_error(table, table->validity);
	return (table->validity);
}

int	parse_input(t_table *table, char *argv[])
{
	table->n_philos = ft_atol(argv[1]);
	table->n_hungry_philos = table->n_philos;
	table->time_to_die = ft_atol(argv[2]) * MSEC;
	table->time_to_eat = ft_atol(argv[3]) * MSEC;
	table->time_to_sleep = ft_atol(argv[4]) * MSEC;
	if (argv[5])
		table->n_limit_meals = ft_atol(argv[5]);
	else
		table->n_limit_meals = 0;
	table->sim_status = RUNNING;
	pthread_mutex_init(&table->mutex, NULL);
	if (check_input(table))
		return (BAD_ARGS);
	else
		return (0);
}
