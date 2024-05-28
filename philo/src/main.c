/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:53:07 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/28 14:00:16 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *value)
{
	int		*time;

	time = (int *)value;
	write(1, "Test from threads\n", 18);
	sleep(*time);
	write(1, "Ending thread\n", 14);
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_table	table;
	int		errcode;

	errcode = VALID;
	if (argc < 5 || argc > 6)
		errcode = N_ARGS;
	if (!errcode)
		errcode = parse_input(&table, argv);
	if (!errcode)
		errcode = init_philos(&table);
	if (!errcode)
	{
		start_sim(&table);
		safe_free(&table);
	}
	if (errcode)
		print_errcode(errcode, argc);
	return (errcode);
}
