/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:13:09 by gnyssens          #+#    #+#             */
/*   Updated: 2024/11/28 00:14:34 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	int			i;
	t_data		*data;
	t_philo		*philos;

	data = (t_data *)arg;
	philos = data->philos;
	while (data->someone_dead == 0)
	{
		
	}
}
