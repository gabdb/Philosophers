/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:11:04 by gnyssens          #+#    #+#             */
/*   Updated: 2024/11/23 18:33:45 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parsing(int ac, char **av)
{
	long long	x;

	if (ac < 5 || ac > 6)
		return (perror("wrong number of arguments !\n"), 0); //p-e meme exit
	x = my_atoi(av[1]);
	if (x < 1 || x > 300)
		return (perror("wrong number of philos !\n"), 0);
	x = my_atoi(av[2]);
	if (x < 1 || x > 1000000) //choisi 1M au hasard, on verra bien
		return (perror("wrong 'time to die' !\n"), 0);
	x = my_atoi(av[3]);
	if (x < 1 || x > 1000000)
		return (perror("wrong 'time to eat' !\n"), 0);
	x = my_atoi(av[4]);
	if (x < 1 || x > 1000000)
		return (perror("wrong 'time to sleep' !\n"), 0);
	if (6 == ac)
	{
		x = my_atoi(av[5]);
		if (x < 1 || x > 1000) //1000 valeur arbitraire
			return (perror("wrong 'number of meals' !\n"), 0);
	}
	return (1);
}
