/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:17:35 by gnyssens          #+#    #+#             */
/*   Updated: 2024/11/26 18:21:47 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_philos)
	{
		data->philos[i].data = data;
		data->philos[i].id = 1 + i;
		data->philos[i].is_eating = 0;
		data->philos[i].last_meal_time = data->start_time;
		data->philos[i].meals = 0;
		data->philos[i].left_fork = i;
		if (i < data->number_philos - 1)
			data->philos[i].right_fork = i + 1;
		else
			data->philos[i].right_fork = 0; //dernier philo
		i++;
	}
}

int	initialize_data(int ac, char **av, t_data *data)
{
	int	nb;

	data->number_philos = (int)my_atoi(av[1]);
	data->time_to_die = my_atoi(av[2]);
	data->time_to_eat = my_atoi(av[3]);
	data->time_to_sleep = my_atoi(av[4]);
	if (av[5])
		data->number_meals = (int)my_atoi(av[5]);
	else
		data->number_meals = -1; //jsp trop, juste pr dire infini
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->number_philos);
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->number_philos);
	if (!(data->philos) || !(data->forks))
		return (write(2, "malloc failed !\n", 16), 0);
	nb = -1;
	while (++nb < data->number_philos)
	{
		if (pthread_mutex_init(data->forks + nb, NULL) != 0)
			return (big_free(data->forks, data->philos)
				  , write(2, "mutex init failed !\n", 20), 0);
	}
    if (pthread_mutex_init(&data->print_mutex, NULL) != 0) //yen aura d'autres !
        return (write(2, "mutex init failed !\n", 20), 1);
    data->start_time = get_time_ms();
	data->someone_dead = 0;
	return (1);
}
