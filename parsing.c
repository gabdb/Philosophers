/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:11:04 by gnyssens          #+#    #+#             */
/*   Updated: 2024/12/26 15:12:17 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	non_numeric(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] > '9' || av[i][j] < '0')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	parsing(int ac, char **av)
{
	long long	x;

	if (non_numeric(ac, av))
		return (write(2, "invalid character input !\n", 26), 0);
	if (ac < 5 || ac > 6)
		return (write(2, "wrong number of arguments !\n", 28), 0);
	x = my_atoi(av[1]);
	if (x < 1 || x > 300)
		return (write(2, "wrong number of philos !\n", 25), 0);
	x = my_atoi(av[2]);
	if (x < 1 || x > 100000)
		return (write(2, "wrong 'time to die' !\n", 22), 0);
	x = my_atoi(av[3]);
	if (x < 1 || x > 100000)
		return (write(2, "wrong 'time to eat' !\n", 22), 0);
	x = my_atoi(av[4]);
	if (x < 1 || x > 100000)
		return (write(2, "wrong 'time to sleep' !\n", 24), 0);
	if (6 == ac)
	{
		x = my_atoi(av[5]);
		if (x < 1 || x > 1000)
			return (write(2, "wrong 'number of meals' !\n", 26), 0);
	}
	return (1);
}
