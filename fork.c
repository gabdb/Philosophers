/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:18:13 by gnyssens          #+#    #+#             */
/*   Updated: 2024/12/27 16:53:34 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pmu(pthread_mutex_t *mutex)
{
	pthread_mutex_unlock(mutex);
}

int	take_forks(t_data *data, t_philo *philo)
{
	int	lf;
	int	rf;

	lf = philo->left_fork;
	if (philo->id == data->number_philos)
		lf = philo->right_fork;
	pthread_mutex_lock(data->forks + lf);
	pthread_mutex_lock(&data->print_mutex);
	if (is_someone_dead(data))
		return (pmu(data->forks + lf), pmu(&data->print_mutex), 1);
	printf("%lld %d has taken a fork\n", get_time_ms()
		- data->start_time, philo->id);
	pthread_mutex_unlock(&data->print_mutex);
	rf = philo->right_fork;
	if (philo->id == data->number_philos)
		rf = philo->left_fork;
	pthread_mutex_lock(data->forks + rf);
	pthread_mutex_lock(&data->print_mutex);
	if (is_someone_dead(data))
		return (pthread_mutex_unlock(data->forks + lf),
			pmu(data->forks + rf), pmu(&data->print_mutex), 1);
	printf("%lld %d has taken a fork\n", get_time_ms()
		- data->start_time, philo->id);
	pthread_mutex_unlock(&data->print_mutex);
	return (0);
}
