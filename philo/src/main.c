/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:53:07 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/15 18:15:04 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_table	*table;
	int		errcode;

	errcode = VALID;
	if (argc < 5 || argc > 6)
		errcode = N_ARGS;
	table = (t_table *)malloc(sizeof(t_table));
	if (!errcode)
		errcode = parse_input(table, argv);
	if (!errcode)
		errcode = init_philos(table);
	if (!errcode)
		errcode = init_forks(table);
	if (!errcode)
	{
		print_valid_input(table);
		start_sim(table);
		end_sim(table);
		safe_free(table, errcode);
	}
	if (errcode)
	{
		safe_free(table, errcode);
		print_errcode(errcode, argc);
	}
	return (errcode);
}
