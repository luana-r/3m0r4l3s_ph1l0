/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_reaper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 21:45:30 by marvin            #+#    #+#             */
/*   Updated: 2025/01/23 21:45:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_died(t_philo *philo)
{
	long	elapsed;
	long	time_to_die;
	long	current_time;
	long	last_meal_time;

	if (get_int(&philo->philo_mutex, &philo->max_meal) == 1)
		return (0);
	current_time = gettime(MILLISECOND);
	last_meal_time = get_long(&philo->philo_mutex, &philo->last_meal_time);
	elapsed = current_time - last_meal_time;
	time_to_die = (philo->table->time_die) / 1000;
	if (elapsed > time_to_die)
		return (1);
	return (0);
}

void	*check_dinner(void *data) //1:41 ele não declara, mas puxa do ponteiro void?
{
	t_table			*table;
	int				i;

	table = (t_table *)data;
	while (!all_philos_running(&table->table_mutex, &table->philos_running_nbr, table->philo_nbr))
		;
	while (!simulation_end(table))
	{
		i = -1;
		while (++i < table->philo_nbr && !simulation_end(table))
		{

			if (philo_died(table->philos + i)) //1:43
			{
				set_int(&table->table_mutex, &table->end, 1);
				write_status(DIED, table->philos + i, DEBUG_MODE);
			}
		}
	}
	return (NULL);
}
