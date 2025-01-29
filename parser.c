/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:52:53 by emorales          #+#    #+#             */
/*   Updated: 2025/01/24 16:52:53 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

const char	*validate_input(const char *arg)
{
	// int			len;
	const char	*nbr;

	// len = 0;
	//printf("char passado para validate: %s\n", arg);
	while (is_space(*arg)) //pular espaços
		arg++;
	if (*arg == '+')
		arg++;
	else if (*arg == '-')
		error_exit("Only positive arguments are accepted\n");
	if (is_digit(*arg) != 1)
	{
		//printf("char: %s ", arg);
		error_exit("The input is not a valid number\n");
	}
	nbr = arg;
	//printf("validate pós nbr (%s) =  arg(%s)\n", nbr, arg);
	/*while (is_digit(*arg++) == 1)
		len++;
	printf("len: %d\n", len);
	printf("validate pós soma len: %s\n", arg);
	if (len > 10)
		error_exit("Argument is larger than INT_MAX\n");
	printf("validate final nbr (%s) =  arg(%s)\n", nbr, arg);*/
	return (nbr);
}

long	ft_atol(const char *arg)
{
	long	nbr;

	nbr = 0;
	//printf("char passado para atol: %s\n", arg);
	arg = validate_input(arg);
	//printf("char %s validado pela atol\n", arg);
	while (is_digit(*arg))
	{
		nbr = (nbr * 10) + (*arg - 48);
		arg++;
	}
	if (nbr > INT_MAX)
		error_exit("Argument is larger than INT_MAX\n");
	return (nbr);
}

void	parse_input(t_table *table, char **argv)
{
	/*printf("argv[0] %s\n", argv[0]);
	printf("argv[1] %s\n", argv[1]);
	printf("argv[2] %s\n", argv[2]);
	printf("argv[3] %s\n", argv[3]);
	printf("argv[4] %s\n", argv[4]);*/
	table->philo_nbr = ft_atol(argv[1]);
	//printf("philo_nbr %ld\n", table->philo_nbr);
	table->time_die = ft_atol(argv[2]) * 1000;
	//printf("time_die %ld\n", table->time_die);
	table->time_eat = ft_atol(argv[3]) * 1000;
	//printf("time_eat %ld\n", table->time_eat);
	table->time_sleep = ft_atol(argv[4]) * 1000;
	//printf("time_sleep %ld\n", table->time_sleep);
	if (table->time_die < 6000 || table->time_eat < 6000
		|| table->time_sleep < 6000)
	{
		/*printf("philo nbr %ld\n", table->philo_nbr);
		printf("time to die %ld\n", table->time_die);
		printf("time to eat %ld\n", table->time_eat);
		printf("time to sleep %ld\n", table->time_sleep);*/
		error_exit("Use a time larger than 60 ms\n");
	}
	if (argv[5])
	{
		table->limit_meal = ft_atol(argv[5]);
		//printf("limit_meal %ld\n", table->limit_meal);
	}
	else
		table->limit_meal = -1;
}
