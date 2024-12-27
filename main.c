/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:54:30 by gnyssens          #+#    #+#             */
/*   Updated: 2024/12/27 17:34:02 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_solo(t_data *data)
{
	printf("0 1 has taken a fork\n");
	ft_usleep(data->time_to_die, data);
	printf("%lld 1 died", data->time_to_die);
}

int	main(int ac, char **av)
{
	int			i;
	t_data		d;
	pthread_t	check_death;

	if (!parsing(ac, av) || !(initialize_data(av, &d)) || !init_philo(&d))
		return (0);
	if (1 == d.number_philos)
		return (handle_solo(&d), free_destroy(&d));
	i = -1;
	while (++i < d.number_philos)
	{
		if (pthread_create(&d.philos[i].thread, NULL, routine, d.philos + i))
			return (free_destroy(&d), write(2, "Error thread\n", 13), 1);
	}
	if (pthread_create(&check_death, NULL, check_dead, &d) != 0)
		return (free_destroy(&d), write(2, "Error thread\n", 13), 1);
	i = -1;
	while (++i < d.number_philos)
	{
		if (pthread_join(d.philos[i].thread, NULL))
			return (free_destroy(&d), write(2, "Error join\n", 11), 1);
	}
	if (pthread_join(check_death, NULL))
		return (free_destroy(&d), write(2, "Error join\n", 11), 1);
	return (free_destroy(&d), 0);
}
