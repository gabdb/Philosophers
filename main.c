/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:54:30 by gnyssens          #+#    #+#             */
/*   Updated: 2024/11/26 18:48:48 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_solo(t_data *data)
{
	printf("0 1 has taken a fork");
	usleep(data->time_to_die * 1000);
	printf("%lld 1 died", data->time_to_die);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (!parsing(ac, av) || !(initialize_data(ac, av, &data)))
		return (1);
	init_philo(&data);
	if (1 == data.number_philos)
	{
		handle_solo(&data);
		return (free_and_destroy(&data));
	}
	return (0);
}
