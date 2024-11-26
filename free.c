/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:43:16 by gnyssens          #+#    #+#             */
/*   Updated: 2024/11/26 18:51:13 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	big_free(pthread_mutex_t *forks, struct s_philo *philos)
{
	free(forks);
	free(philos);
}

int	free_and_destroy(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_philos)
		pthread_mutex_destroy(data->forks + i);
	pthread_mutex_destroy(&data->print_mutex); //yen aura d'autres ! style un thread qui check en permanence si ya un mort
	free(data->forks);
	free(data->philos);
	return (0);
}
