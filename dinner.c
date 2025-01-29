/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:32:09 by marvin            #+#    #+#             */
/*   Updated: 2025/01/23 16:32:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*lone_philosopher(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	set_long(&(philo->philo_mutex), &philo->last_meal_time, gettime(MILLISECOND));
	increase_long(&philo->table->table_mutex, &philo->table->philos_running_nbr);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	while (!simulation_end(philo->table))
		usleep(100);
	return (NULL);
}

void	think(t_philo *philo, int presim)
{
	long	time_eat;
	long	time_sleep;
	long	time_think;

	if (presim == 0)
		write_status(THINKING, philo, DEBUG_MODE);
	if (philo->table->philo_nbr % 2 == 0) //sistema já justo 2:05:30
		return ;
	time_eat = philo->table->time_eat;
	time_sleep = philo->table->time_sleep;
	time_think = time_eat * 2 - time_sleep; //2:06:25
	if (time_think < 0)
		time_think = 0;
	ft_usleep(time_think * 0.3, philo->table); //defasagem de 30% 2:07:10
}

void	eat(t_philo *philo)
{
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	philo->meal_counter++; //1:30:24
	write_status(EATING, philo, DEBUG_MODE);
	ft_usleep(philo->table->time_eat, philo->table);
	if (philo->table->limit_meal > 0
		&& philo->meal_counter == philo->table->limit_meal)
	{
		set_int(&philo->philo_mutex, &philo->max_meal, 1);
	}
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}

void	*dinner(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_philos(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND)); //1:38
	increase_long(&philo->table->table_mutex, &philo->table->philos_running_nbr);
	gap_odd_philos(philo); //para evitar injustiça, filósofo acorda e ja come
	while (!simulation_end (philo->table))
	{
		if (get_int(&philo->philo_mutex, &philo->max_meal) == 1)
			break ;
		eat(philo);
		write_status(SLEEPING, philo, DEBUG_MODE);
		ft_usleep(philo->table->time_sleep, philo->table);
		think(philo, 0);
	}
	return (NULL);
}

void	start_simulation(t_table *table)
{
	int		i;
	t_philo	*first_philo;

	i = -1;
	table->time_start = gettime(MILLISECOND);
	if (table->limit_meal == 0)
		return ;
	else if (table->philo_nbr == 1)
	{
		first_philo = &table->philos[0];
		safe_thread_handle(&first_philo->thread_id, lone_philosopher, first_philo, CREATE);
	}
	else
	{
		while (++i < table->philo_nbr)
			safe_thread_handle(&table->philos[i].thread_id, dinner, &table->philos[i], CREATE);
	}
	safe_thread_handle(&table->grim_reaper, check_dinner, table, CREATE);
	set_int(&table->table_mutex, &table->everybody_ready, 1);
	i = -1;
	while (++i < table->philo_nbr)
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
	set_int(&table->table_mutex, &table->end, 1);
	safe_thread_handle(&table->grim_reaper, NULL, NULL, JOIN); //1:51:29
}
