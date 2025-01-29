/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:42:13 by marvin            #+#    #+#             */
/*   Updated: 2025/01/23 19:42:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_exit(char *error)
{
	printf("%s", error);
	exit(EXIT_FAILURE); //não pode usar exit
}

long	gettime(t_tcode time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_exit("Gettimeofday failed.\n");
	if (time_code == SECOND)
		return (tv.tv_sec + (tv.tv_usec / 1000000));
	else if (time_code == MILLISECOND)
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	else if (time_code == MICROSECOND)
		return ((tv.tv_sec * 1000000) + tv.tv_usec);
	else
		error_exit("Wrong input to gettime.\n");
	return (0);
}

void	ft_usleep(long sleep_time, t_table *table)
{
	long	start;
	long	total_time;
	long	remaining_time;

	start = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start < sleep_time)
	{
		if (simulation_end(table))
			break ;
		total_time = gettime(MICROSECOND) - start;
		remaining_time = sleep_time - total_time;
		if (remaining_time > 1000) //1:20:49
			usleep (remaining_time / 2); //"garantia" acima de 1 milisec
		else
			while (gettime(MICROSECOND) - start < sleep_time) //travo a cpu pra mim
				;
	}
}

void	clean(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i++ < table->philo_nbr)
	{
		philo = table->philos + i;
		safe_mutex_handle(&philo->philo_mutex, DESTROY);
	}
	safe_mutex_handle(&table->write_mutex, DESTROY);
	safe_mutex_handle(&table->table_mutex, DESTROY);
	free(table->forks);
	free(table->philos);
}
