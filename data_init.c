/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:50:13 by emorales          #+#    #+#             */
/*   Updated: 2025/01/24 16:50:13 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	assign_forks(t_philo *philo, t_fork *forks, int philo_pos)
{
	int	philo_nbr; //53:00

	philo_nbr = philo->table->philo_nbr;
	philo->first_fork = &forks[(philo_pos + 1) % philo_nbr];
	philo->second_fork = &forks[philo_pos];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_pos];
		philo->second_fork = &forks[(philo_pos + 1) % philo_nbr];
	}
}

void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	printf("entrei no philo_init\n");
	while (i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->max_meal = 0;
		philo->meal_counter = 0;
		philo->table = table;
		printf("philo_mutex ");
		safe_mutex_handle(&philo->philo_mutex, INIT);
		assign_forks(philo, table->forks, i);
		i++;
	}
	printf("conclui no philo_init\n");
}

void	data_init(t_table *table)
{
	int	i;

	//printf("entrei no data_init\n");
	table->end = 0;
	table->everybody_ready = 0;
	table->philos_running_nbr = 0;
	table->philos = safe_malloc(sizeof(t_philo) * table->philo_nbr);
	table->forks = safe_malloc(sizeof(t_fork) * table->philo_nbr);
	printf("table_mutex ");
	safe_mutex_handle(&table->table_mutex, INIT);
	printf("write_mutex ");
	safe_mutex_handle(&table->write_mutex, INIT);
	printf("mutexes iniciados\n");
	i = 0;
	while (i < table->philo_nbr)
	{
		printf("fork_mutex ");
		safe_mutex_handle(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
		i++;
		//printf("mutex bem sucedido\n");
	}
	//printf("entrando no philo_init\n");
	philo_init(table);
}
