/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:18:13 by gnyssens          #+#    #+#             */
/*   Updated: 2024/12/27 15:35:31 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
int	last_takes_forks(t_data *data, t_philo *philo)
{
	int	lf;
	int	rf;

	rf = philo->right_fork;
	pthread_mutex_lock(data->forks + rf);
	if (data->someone_dead)
		return (pthread_mutex_unlock(data->forks + rf), 1);
	pthread_mutex_lock(&data->print_mutex);
	printf("%lld %d has taken a fork\n", get_time_ms()
		- data->start_time, philo->id);
	pthread_mutex_unlock(&data->print_mutex);
	lf = philo->left_fork;
	pthread_mutex_lock(data->forks + lf);
	if (data->someone_dead)
		return (pthread_mutex_unlock(data->forks + rf),
			pthread_mutex_unlock(data->forks + lf), 1);
	pthread_mutex_lock(&data->print_mutex);
	printf("%lld %d has taken a fork\n", get_time_ms()
		- data->start_time, philo->id);
	pthread_mutex_unlock(&data->print_mutex);
	return (0);
}

int	manage_forks(t_data *data, t_philo *philo)
{
	int	result;

	if (philo->id < data->number_philos)
		result = take_forks(data, philo);
	else
		result = last_takes_forks(data, philo);
	return (result);
}
*/

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
		return (pthread_mutex_unlock(data->forks + lf), pthread_mutex_unlock(&data->print_mutex), 1);
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
			pthread_mutex_unlock(data->forks + rf), pthread_mutex_unlock(&data->print_mutex), 1);
	printf("%lld %d has taken a fork\n", get_time_ms()
		- data->start_time, philo->id);
	pthread_mutex_unlock(&data->print_mutex);
	return (0);
}
