/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:37:01 by marvin            #+#    #+#             */
/*   Updated: 2025/01/23 19:37:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_philos(t_table *table)
{
	//printf("entrei na wait all philos\n");
	while (!get_int(&table->table_mutex, &table->everybody_ready))
		;
}

int	all_philos_running(pthread_mutex_t *mutex, long *philos, long philo_nbr)
{
	int	ret;

	ret = 0;
	safe_mutex_handle(mutex, LOCK);
	if (*philos == philo_nbr)
		ret = 1;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

void	increase_long(pthread_mutex_t *mutex, long *value)
{
	safe_mutex_handle(mutex, LOCK);
	(*value)++;
	safe_mutex_handle(mutex, UNLOCK);
}

void	increase_int(pthread_mutex_t *mutex, int *value)
{
	safe_mutex_handle(mutex, LOCK);
	(*value)++;
	safe_mutex_handle(mutex, UNLOCK);
}

void	gap_odd_philos(t_philo *philo)
{
	if (philo->table->philo_nbr % 2 == 0)
	{
		if (philo->id % 2 == 0)
			ft_usleep(30000, philo->table);
	}
	else
	{
		if (philo->id % 2 == 1)
			think(philo, 1);
	}
}