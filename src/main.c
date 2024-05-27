/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:53:07 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/27 16:53:50 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine(void *value)
{
	int		*time;

	time = (int *)value;
	/*pthread_mutex_lock(&mutex);*/
	write(1, "Test from threads\n", 18);
	sleep(*time);
	write(1, "Ending thread\n", 14);
	/*pthread_mutex_unlock(&mutex);*/
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_table	table;

	if (argc > 4 && argc < 7)
	{
		parse_input(&table, argv);
	}
	/*pthread_mutex_init(&mutex, NULL);*/
	/*(void)argv;*/
	/*if (!pthread_create(&t1, NULL, &routine, (void *) &v1))*/
		/*return (1);*/
	/*if (!pthread_create(&t2, NULL, &routine, (void *) &v2))*/
		/*return (2);*/
	return (0);
}
