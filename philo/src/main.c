/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:53:07 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/27 19:04:08 by jcummins         ###   ########.fr       */
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

	if (argc < 5 || argc > 6)
	{
		printf("Error: Incorrect number of arguments\n");
		return (1);
	}
	parse_input(&table, argv);
	return (0);
}
