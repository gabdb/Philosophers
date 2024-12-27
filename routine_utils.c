/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:24:35 by gnyssens          #+#    #+#             */
/*   Updated: 2024/12/27 16:33:50 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_last_meal(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->death_mutex);
	if (get_time_ms() - philo->last_meal_time > data->time_to_die)
	{
		philo->is_dead = 1;
		data->someone_dead = 1;
		data->dead_id = philo->id;
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->death_mutex);
	return (0);
}

int	is_someone_dead(t_data *data)
{
	pthread_mutex_lock(&data->death_mutex);
	if (data->someone_dead)
	{
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->death_mutex);
	return (0);
}

int	ft_eat(t_data *data, t_philo *philo)
{
	int	lf;
	int	rf;

	lf = philo->left_fork;
	rf = philo->right_fork;
	philo->is_eating = 1;
	pthread_mutex_lock(&data->print_mutex);
	if (is_someone_dead(data))
	{
		pthread_mutex_unlock(data->forks + lf);
		pthread_mutex_unlock(data->forks + rf);
		pthread_mutex_unlock(&data->print_mutex);
		return (1);
	}
	printf("%lld %d is eating\n", get_time_ms() - data->start_time, philo->id);
	pthread_mutex_unlock(&data->print_mutex);
	philo->last_meal_time = get_time_ms();
	ft_usleep(data->time_to_eat, data);
	pthread_mutex_unlock(data->forks + lf);
	pthread_mutex_unlock(data->forks + rf);
	philo->is_eating = 0;
	philo->meals_eaten += 1;
	return (0);
}

int	ft_sieste(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->print_mutex);
	if (is_someone_dead(data))
		return (pthread_mutex_unlock(&data->print_mutex), 1);
	printf("%lld %d is sleeping\n", get_time_ms()
		- data->start_time, philo->id);
	pthread_mutex_unlock(&data->print_mutex);
	usleep(data->time_to_sleep * 1000);
	return (0);
}
