/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 20:31:35 by marvin            #+#    #+#             */
/*   Updated: 2025/01/23 20:31:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status_debug(t_philo_status status, t_philo *philo, long elapsed)
{
	if (status == TAKE_FIRST_FORK && !simulation_end(philo->table))
	{
		printf("%-6ld ", elapsed);
		printf("%d 1º n. %d\n", philo->id, philo->first_fork->fork_id);
	}
	else if (status == TAKE_SECOND_FORK && !simulation_end(philo->table))
	{
		printf("%-6ld ", elapsed);
		printf("%d 2º n. %d\n", philo->id, philo->second_fork->fork_id);
	}
	else if (status == EATING && !simulation_end(philo->table))
	{
		printf("%-6ld ", elapsed);
		printf("%d eats, %ldx\n", philo->id, philo->meal_counter);
	}
	else if (status == SLEEPING && !simulation_end(philo->table))
		printf("%-6ld" " %d is sleeping\n", elapsed, philo->id);
	else if (status == THINKING && !simulation_end(philo->table))
		printf("%-6ld" " %d is thinking\n", elapsed, philo->id);
	else if (status == DIED)
		printf("%-6ld" " %d died\n", elapsed, philo->id);
}

void	write_status(t_philo_status status, t_philo *philo, int debug)
{
	long	elapsed;

	elapsed = gettime(MILLISECOND) - philo->table->time_start;
	safe_mutex_handle(&philo->table->write_mutex, LOCK);
	if (debug == 1)
		write_status_debug(status, philo, elapsed);
	else
	{
		if ((status == TAKE_FIRST_FORK
				|| status == TAKE_SECOND_FORK) && !simulation_end(philo->table))
			printf("%-6ld" " %d has taken a fork\n", elapsed, philo->id);
		else if (status == EATING && !simulation_end(philo->table))
			printf("%-6ld" " %d is eating\n", elapsed, philo->id);
		else if (status == SLEEPING && !simulation_end(philo->table))
			printf("%-6ld" " %d is sleeping\n", elapsed, philo->id);
		else if (status == THINKING && !simulation_end(philo->table))
			printf("%-6ld" " %d is thinking\n", elapsed, philo->id);
		else if (status == DIED)
			printf("%-6ld" " %d died\n", elapsed, philo->id);
	}
	safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}
