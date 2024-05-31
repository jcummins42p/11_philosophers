/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:53:07 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/31 16:54:22 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*wait(void *value)
{
	int		*time;

	time = (int *)value;
	/*write(1, "Test from threads\n", 18);*/
	printf("Philo %d is waiting\n", *time);
	sleep(*time);
	write(1, "Ending thread\n", 14);
	return (NULL);
}

void	*take_fork(t_fork *fork, t_philo *philo)
{
	if (fork->id == philo->id)
		printf("Philo has taken the fork to their LEFT\n");
	else if (fork->id == philo->id + 1)
		printf("Philo has taken the fork to their RIGHT\n");
	else
		printf("Philo %d has taken A FORBIDDEN FORK (%d)\n", philo->id, fork->id);
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
