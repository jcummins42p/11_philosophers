/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <jcummins@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:56:55 by jcummins          #+#    #+#             */
/*   Updated: 2024/07/16 19:41:44 by jcummins         ###   ########.fr       */
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
# define MSEC 1000
# define DEATH_MOD 850

typedef enum e_timecode
{
	SEC,
	MLSEC,
	MUSEC
}	t_timecode;

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
	MUTEX_FAIL,
	TIME_FAIL,
	THREAD_FAIL
}	t_errcode;

typedef enum e_endcode
{
	WAITING,
	RUNNING,
	END_FULL,
	END_DEAD
}	t_endcode;

typedef enum e_state
{
	THINKING,
	HUNGRY,
	FORKING,
	EATING,
	SLEEPING,
	FULL,
	DEAD,
	DEBUG,
	LMT
}	t_state;

typedef pthread_mutex_t	t_mutex;

typedef struct s_table	t_table;
typedef struct s_philo	t_philo;
typedef struct s_fork	t_fork;
typedef long long		t_timestamp;

typedef struct s_table
{
	long			n_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				n_limit_meals;
	int				n_hungry_philos;
	struct timeval	start_time;
	int				sim_status;
	t_fork			**forks;
	t_philo			**philos;
	int				validity;
	int				errcode;
	pthread_t		monitor_id;
	t_mutex			mutex;
	t_mutex			printf_mutex;
}	t_table;

typedef struct s_philo
{
	int				id;
	pthread_t		thread_id;
	int				status;
	bool				full;
	t_fork			*l_fork;
	t_fork			*r_fork;
	int				n_meals;
	struct timeval	start_time;
	t_timestamp		last_meal_time;
	t_table			*table;
	t_mutex			mutex;
}	t_philo;

typedef struct s_fork
{
	t_mutex	mutex;
	int		id;
}	t_fork;

//	safe_handlers.c
void		*safe_malloc(size_t bytes, t_table *table);
void		safe_free(t_table *table, t_errcode errcode);
void		safe_mutex(t_mutex *mtx, t_mutex_code mutex_code);
void		error_mutex(int status, t_mutex_code mutex_code);

//	print_helpers.c
void		printf_mutex(char *str, t_table *table);
void		print_ts(t_table *table, t_philo *philo, int state);

//	setters.c
void		set_sim_status(t_table *table, int newval);
void		set_philo_status(t_philo *philo, int newval);
void		set_increment(t_mutex *mtx, int *old);
void		set_decrement(t_mutex *mtx, int *old);
void		set_ts(t_mutex *mtx, t_timestamp *old, t_timestamp new);

//	getters.c
int			get_sim_status(t_table *table);
int			get_philo_status(t_philo *philo);
int			get_int(t_mutex *mtx, int *val);
t_timestamp	get_ts(t_mutex *mtx, t_timestamp *val);

//	bool_set_get.c
void		set_bool(t_mutex *mtx, bool *oldval, bool newval);
bool		get_bool(t_mutex *mtx, bool *getval);

//	errors.c
void		error_exit(int errcode);
int			check_input(t_table *table);
void		print_errcode(int errcode, int argc);
void		print_error(t_table *table, int err);

//	parse_input.c
void		print_valid_input(t_table *table);
int			parse_input(t_table *table, char *argv[]);

//	init.c
int			init_table(t_table *table, char *argv[]);
int			init_philos(t_table *table);
int			init_forks(t_table *table);

//	utils.c
void		update_status(t_table *table, t_philo *philo, int *t, int *p);
int			ft_strlen(const char *str);
long		ft_atol(const char *str);

//	sim.c
int			spawn_philos(pthread_t *thread_id, t_philo *philo);
int			end_sim(t_table *table);
int			start_sim(t_table *table);

//	splash.c
void		splash(void);

//	psleep.c
t_timestamp	ts_since_ts(t_timestamp t_start, t_timestamp t_end);
t_timestamp	ts_since_tv(struct timeval t_start);
t_timestamp	gettime(t_timecode time_code);
void		psleep(t_timestamp total, t_table *table);
void		pusleep(t_timestamp remaining);

//	fork_funcs.c
void		drop_both_forks(t_philo *philo);
void		take_fork_one(t_table *table, t_philo *philo);
void		take_fork_two(t_table *table, t_philo *philo);
void		take_fork(t_table *table, t_fork *fork, t_philo *philo);

//	routines.c
void		*start_routine(void *arg);

//	monitor.c
void		*start_monitor(void *arg);

#endif
