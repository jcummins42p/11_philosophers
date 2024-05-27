/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:11:30 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/27 19:03:25 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

long	ft_atol(const char *str)
{
	long	out;
	int		i;

	i = 0;
	out = 0;
	while (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			if (out)
				return (out);
			else
				return (-1);
		}
		out = (out * 10) + (str[i++] - '0');
		if (out > INT_MAX)
			return (-1);
	}
	return (out);
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
		return (1);
	else
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
	return (0);
}

void	table_init(t_table *table)
{
	(void)table;
}
