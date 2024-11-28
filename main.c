/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:54:30 by gnyssens          #+#    #+#             */
/*   Updated: 2024/11/28 18:36:30 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_solo(t_data *data)
{
	printf("0 1 has taken a fork\n");
	usleep(data->time_to_die * 1000);
	printf("%lld 1 died", data->time_to_die);
}

int	main(int ac, char **av)
{
	int			i;
	t_data		data;
	pthread_t	check_death;

	if (!parsing(ac, av) || !(initialize_data(av, &data)))
		return (0);
	init_philo(&data);
	if (1 == data.number_philos)
	{
		handle_solo(&data);
		return (free_and_destroy(&data));
	}
	if (pthread_create(&check_death, NULL, check_dead, &data) != 0)
		return (free_and_destroy(&data), write(2, "failed to create thread\n", 24), 1);
	i = -1;
	while (++i < data.number_philos)
	{
		if (pthread_create(&data.philos[i].thread, NULL, routine, data.philos + i) != 0)
			return (free_and_destroy(&data), write(2, "failed to create thread\n", 24), 1);
	}
	i = -1;
	while (++i < data.number_philos)
	{
		if (pthread_join(data.philos[i].thread, NULL) || pthread_join(check_death, NULL))
			return (free_and_destroy(&data), write(2, "problem with pthread_join\n", 26), 1);
	}

	free_and_destroy(&data);
	pthread_mutex_destroy(&data.print_mutex);
	return (0);
}
