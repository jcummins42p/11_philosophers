/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:11:30 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/28 12:05:34 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_valid_input(t_table *table)
{
	printf("Input valid:\n");
	printf("\tNumber of philosophers is %ld\n", table->n_philos);
	printf("\tTime to die is %ld\n", table->time_to_die);
	printf("\tTime to eat is %ld\n", table->time_to_eat);
	printf("\tTime to sleep is %ld\n", table->time_to_sleep);
	if (table->n_limit_meals)
		printf("\tMeal limit is %ld\n", table->n_limit_meals);
	else
		printf("\tNo meal limit set\n");
}

int	check_input(t_table *table)
{
	table->validity = 0;
	if (table->n_philos < 2)
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
	table->time_to_die = ft_atol(argv[2]) * 1e3;
	table->time_to_eat = ft_atol(argv[3]) * 1e3;
	table->time_to_sleep = ft_atol(argv[4]) * 1e3;
	if (argv[5])
		table->n_limit_meals = ft_atol(argv[5]);
	else
		table->n_limit_meals = 0;
	if (check_input(table))
		return (BAD_ARGS);
	else
		print_valid_input(table);
	return (0);
}
