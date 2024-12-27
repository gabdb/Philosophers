/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:13:09 by gnyssens          #+#    #+#             */
/*   Updated: 2024/12/27 16:28:57 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_util(t_data *data, int nb)
{
	pthread_mutex_lock(&data->death_mutex);
	if (data->someone_dead == 1)
	{
		pthread_mutex_lock(&data->print_mutex);
		printf("%lld %d is dead\n", get_time_ms()
			- data->start_time, data->dead_id);
		pthread_mutex_unlock(&data->print_mutex);
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->death_mutex);
	if (!data->philos[nb].is_eating && get_time_ms()
		- data->philos[nb].last_meal_time > data->time_to_die)
	{
		pthread_mutex_lock(&data->death_mutex);
		data->someone_dead = 1;
		data->dead_id = data->philos[nb].id;
		pthread_mutex_unlock(&data->death_mutex);
		pthread_mutex_lock(&data->print_mutex);
		printf("%lld %d is dead\n", get_time_ms()
			- data->start_time, data->dead_id);
		pthread_mutex_unlock(&data->print_mutex);
		return (1);
	}
	return (0);
}

int	all_meals_eaten(t_data *data)
{
	t_philo		*philos;
	int			nb;

	if (data->number_meals == -1)
		return (0);
	philos = data->philos;
	nb = 0;
	while (nb < data->number_philos)
	{
		if (philos[nb].meals_eaten < data->number_meals)
			return (0);
		nb++;
	}
	return (1);
}

void	*check_dead(void *arg)
{
	t_data	*data;
	int		nb;

	data = (t_data *)arg;
	while (1)
	{
		nb = 0;
		while (nb < data->number_philos)
		{
			if (dead_util(data, nb))
				return (NULL);
			nb++;
		}
		if (all_meals_eaten(data) == 0)
			usleep(1000);
		else
			break ;
	}
	return (NULL);
}

void	mini_pause(t_data *data, int id)
{
	if (id % 2 == 0)
		usleep(data->time_to_eat * 200);
	else if (id == data->number_philos)
		usleep(data->time_to_eat * 800);
}

void	*routine(void *arg)
{
	t_data		*data;
	t_philo		*philo;

	philo = (t_philo *)arg;
	data = philo->data;
	philo->last_meal_time = data->start_time;
	mini_pause(data, philo->id);
	while (1)
	{
		if (is_someone_dead(data) || check_last_meal(data, philo))
			break ;
		if (data->number_meals != -1
			&& philo->meals_eaten >= data->number_meals)
			break ;
		if (take_forks(data, philo))
			break ;
		if (ft_eat(data, philo))
			break ;
		ft_sieste(data, philo);
		if (is_someone_dead(data))
			break ;
		print_mutex_norm(data, philo);
	}
	return (NULL);
}
