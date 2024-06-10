/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:53:07 by jcummins          #+#    #+#             */
/*   Updated: 2024/06/10 18:58:35 by jcummins         ###   ########.fr       */
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

void *take_left_fork(t_table *table, t_philo *philo)
{
	int			target;
	pthread_t	*out;

	target = philo->id;
	out = take_fork(table, table->forks[target], philo);
	return (out);
}

void *take_right_fork(t_table *table, t_philo *philo)
{
	int 		target;
	pthread_t	*out;

	target = (philo->id + 1) % table->n_philos;
	out = take_fork(table, table->forks[target], philo);
	return (out);
}

void *take_fork(t_table *table, t_fork *fork, t_philo *philo)
{
	pthread_mutex_lock(&fork->mutex);
	if (fork->id == philo->id)
	{
		philo->l_fork = fork;
		printf("Philo %d has taken the fork to their LEFT\n", philo->id);
	}
	else if (fork->id == (philo->id + 1) % table->n_philos)
	{
		philo->r_fork = fork;
		printf("Philo %d has taken the fork to their RIGHT\n", philo->id);
	}
	else
		printf("Philo %d got A FORBIDDEN FORK (%d)\n", philo->id, fork->id);
	pthread_mutex_unlock(&fork->mutex);
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
		errcode = init_forks(&table);
	if (!errcode)
	{
		splash();
		sleep(4);
		start_sim(&table);
		safe_free(&table);
	}
	if (errcode)
		print_errcode(errcode, argc);
	return (errcode);
}
