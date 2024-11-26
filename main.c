/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:54:30 by gnyssens          #+#    #+#             */
/*   Updated: 2024/11/26 16:20:33 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	initialize_data(int ac, char **av, t_data *data)
{
	int	i;
	int	nb;

	data->number_philos = (int)my_atoi(av[1]);
	data->time_to_die = my_atoi(av[2]);
	data->time_to_eat = my_atoi(av[3]);
	data->time_to_sleep = my_atoi(av[4]);
	if (av[5])
		data->number_meals = (int)my_atoi(av[5]);
	else
		data->number_meals = -1; //jsp trop, juste pr dire infini
	nb = data->number_philos;
	data->philos = (t_philo *)malloc(sizeof(t_philo) * nb);
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * nb);
	if (!(data->philos) || !(data->forks))
		return (0);
	i = -1;
	while (++i < nb)
	{
		if (pthread_mutex_init(data->forks + i, NULL) != 0)
			return (big_free(data->forks, data->philos)
				  , perror("mutex init failed !\n"), 0);
	}
    data->start_time = get_time_ms();
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (!parsing(ac, av) || !(initialize_data(ac, av, &data)))
		return (1);
	
}
