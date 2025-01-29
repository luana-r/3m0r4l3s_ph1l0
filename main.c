/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 14:17:25 by emorales          #+#    #+#             */
/*   Updated: 2025/01/28 22:22:06 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int argc)
{
	if (argc != 5 && argc != 6)
	{
		error_exit("Wrong number of arguments\n");
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (check_args(argc) == 1)
		return (1);
	parse_input(&table, argv);
	data_init(&table);
	start_simulation(&table);
	clean(&table);
	return (0);
}
