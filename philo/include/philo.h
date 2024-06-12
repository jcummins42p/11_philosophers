/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:56:55 by jcummins          #+#    #+#             */
/*   Updated: 2024/06/12 16:48:55 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>

# define KDEF "\x1B[0m"
# define KRED "\x1B[31m"
# define KGRN "\x1B[32m"
# define KYEL "\x1B[33m"
# define KBLU "\x1B[34m"
# define KMAG "\x1B[35m"
# define KCYN "\x1B[36m"
# define KWHT "\x1B[37m"

# define USEC 1000000

typedef enum e_mutex_code
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH
}	t_mutex_code;

typedef enum e_errcode
{
	VALID,
	N_ARGS,
	BAD_ARGS,
	MALLOC_FAIL,
	TIME_FAIL
}	t_errcode;

typedef enum e_endcode
{
	RUNNING,
	END_FULL,
	END_DEAD
}	t_endcode;

typedef enum e_state
{
	THINKING,
	HUNGRY,
	SLEEPING,
	TAKING_L_FORK,
	TAKING_R_FORK,
	EATING,
	DEAD
}	t_state;

typedef pthread_mutex_t	t_mutex;

typedef struct s_table	t_table;
typedef struct s_philo	t_philo;
typedef struct s_fork	t_fork;
typedef unsigned int	t_timestamp;

typedef struct s_table
{
	long			n_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			n_limit_meals;
	struct timeval	start_time;
	int				end_sim;
	t_fork			**forks;
	t_philo			**philos;
	t_mutex			mutex;
	int				validity;
	pthread_t		monitor_id;
}	t_table;

typedef struct s_fork
{
	t_mutex	mutex;
	int		id;
}	t_fork;

typedef struct s_philo
{
	int			id;
	int			status;
	pthread_t	thread_id;
	t_fork		*l_fork;
	t_fork		*r_fork;
	long		n_meals;
	t_timestamp	last_meal_time;
	bool		full;
	bool		dead;
	t_table		*table;
}	t_philo;

//	safe_handlers.c
void	*safe_malloc(size_t bytes, t_table *table);
void	safe_free(t_table *table);
void	safe_mutex(t_mutex *mtx, t_mutex_code mutex_code);
void	error_mutex(int status, t_mutex_code mutex_code);

//	errors.c
void	error_exit(int errcode);
int		check_input(t_table *table);
void	print_errcode(int errcode, int argc);
void	print_error(t_table *table, int err);

//	parse_input.c
int		parse_input(t_table *table, char *argv[]);

//	init.c
int		init_philos(t_table *table);
int		init_forks(t_table *table);

//	utils.c
int		ft_strlen(const char *str);
long	ft_atol(const char *str);

//	sim.c
void	run_sim(t_table *table);
int		start_sim(t_table *table);

//	splash.c
void	splash(void);

//	psleep.c
t_timestamp	get_time_since(struct timeval t_start);
void	pusleep(unsigned int remaining);

//	routines.c
void	*take_left_fork(t_table *table, t_philo *philo);
void	*take_right_fork(t_table *table, t_philo *philo);
void	*take_fork(t_table *table, t_fork *fork, t_philo *philo);
void	*routine_think(t_table *table);
void	*routine_sleep(t_table *table, t_philo *philo);
void	*routine_eat(t_table *table, t_philo *philo);
void	*routine_run(void *arg);

//	monitor.c
void	*routine_monitor(void *arg);

#endif
