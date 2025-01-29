/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 14:13:10 by emorales          #+#    #+#             */
/*   Updated: 2025/01/28 22:20:58 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>
# include <errno.h>

# define DEBUG_MODE 0

typedef enum e_mcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_mcode;

typedef enum e_tcode
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}	t_tcode;

typedef enum e_philo_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}	t_philo_status;

typedef struct s_table	t_table;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}	t_fork;

typedef struct s_philo
{
	int				id;
	long			meal_counter;
	int				max_meal; //verificar se o filósofo comeu o número max de refeições, 1 full, 0 not full
	long			last_meal_time;
	t_fork			*first_fork;
	t_fork			*second_fork;
	pthread_t		thread_id;
	pthread_mutex_t	philo_mutex;
	t_table			*table;
}	t_philo;

struct s_table
{
	long			philo_nbr;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	long			limit_meal; // -1 caso o parâmetro não entre
	long			time_start;
	int				everybody_ready;
	int				end; // 1 quando um philo morre ou quando todos ficham cheios
	long				philos_running_nbr;
	pthread_t		grim_reaper;
	pthread_mutex_t	table_mutex; //evitar concorrencia ao aler da mesa
	pthread_mutex_t	write_mutex;
	t_fork			*forks;
	t_philo			*philos;
};

//data_init.c
void		assign_forks(t_philo *philo, t_fork *forks, int philo_pos);
void		data_init(t_table *table);
void		philo_init(t_table *table);

//dinner.c
void		*lone_philosopher(void *data);
void		*dinner(void *data);
void		eat(t_philo *philo);
void		start_simulation(t_table *table);
void		think(t_philo *philo, int presim);

//getters_setters.c
int			get_int(pthread_mutex_t *mutex, int *value);
long		get_long(pthread_mutex_t *mutex, long *value);
void		set_int(pthread_mutex_t *mutex, int *dest, int value);
void		set_long(pthread_mutex_t *mutex, long *dest, long value);
int			simulation_end(t_table *table);

//grim_reaper
void		*check_dinner(void *data);
int			philo_died(t_philo *philo);

//main.c
int			check_args(int argc);

//parser
long		ft_atol(const char *arg);
int			is_digit(char c);
int			is_space(char c);
void		parse_input(t_table *table, char **argv);
const char	*validate_input(const char *arg);

//safe_functions.c
void		handle_mutex_errors(int status, t_mcode mcode);
void		handle_thread_errors(int status, t_mcode mcode);
void		*safe_malloc(size_t size);
void		safe_mutex_handle(pthread_mutex_t *mutex, t_mcode mcode);
void		safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_mcode mcode);

//synchro.c
void		wait_all_philos(t_table *table);
int			all_philos_running(pthread_mutex_t *mutex, long *philos, long philo_nbr);
void		increase_long(pthread_mutex_t *mutex, long *value);
void		increase_int(pthread_mutex_t *mutex, int *value);
void		gap_odd_philos(t_philo *philo);

//utils.c
void		clean(t_table *table);
void		error_exit(char *error);
void		ft_usleep(long sleep_time, t_table *table);
long		gettime(t_tcode time_code);

//write.c
void		write_status(t_philo_status status, t_philo *philo, int debug);
void		write_status_debug(t_philo_status status, t_philo *philo, long elapsed);

#endif