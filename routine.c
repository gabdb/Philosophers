/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:13:09 by gnyssens          #+#    #+#             */
/*   Updated: 2024/11/28 18:46:03 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//MAUVAISE CONDITION if ()
void	*check_dead(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1) //pas bonne condition, pcq si ya un number_meals specifie, cv jamais sarreter !!
	{
		if (data->someone_dead)
		{
			pthread_mutex_lock(&data->print_mutex);
			printf("%lld %d is dead\n", get_time_ms() - data->start_time, data->dead_id);
			pthread_mutex_unlock(&data->print_mutex);
			break;
		}
		
		(void) usleep(10); //jsp si necessaire, pr eviter de surchauffer
	}
	return (NULL);
}

void	*routine(void *arg)
{
	int			lf;
	int			rf;
	t_data		*data;
	t_philo		*philo;

	philo = (t_philo *)arg;
	data = philo->data;
	philo->last_meal_time = data->start_time;
	while (1)
	{
		//check death
		if (get_time_ms() - philo->last_meal_time > data->time_to_die)
		{
			philo->is_dead = 1;
			data->someone_dead = 1;
			data->dead_id = philo->id;
			break;
		}
		if (data->number_meals != -1 && philo->meals_eaten >= data->number_meals)
			break;
		if (philo->id % 2 == 0)
			(void) usleep(5000); //sleep 10 ms to avoid bug
		lf = philo->left_fork;
		pthread_mutex_lock(data->forks + lf);
		pthread_mutex_lock(&data->print_mutex);
		printf("%lld %d has taken a fork\n", get_time_ms() - data->start_time, philo->id);
		pthread_mutex_unlock(&data->print_mutex);
		rf = philo->right_fork;
		pthread_mutex_lock(data->forks + rf);
		pthread_mutex_lock(&data->print_mutex);
		printf("%lld %d has taken a fork\n", get_time_ms() - data->start_time, philo->id);
		pthread_mutex_unlock(&data->print_mutex);
		
		//now that philo has 2 forks, and can eat
		
		philo->is_eating = 1;
		pthread_mutex_lock(&data->print_mutex);
		printf("%lld %d is eating\n", get_time_ms() - data->start_time, philo->id);
		pthread_mutex_unlock(&data->print_mutex);
		(void) usleep(data->time_to_eat * 1000);
		pthread_mutex_unlock(data->forks + lf);
		pthread_mutex_unlock(data->forks + rf);
		philo->is_eating = 0;
		philo->last_meal_time = get_time_ms();
		philo->meals_eaten += 1;
		
		//philo has released forks and will sleep
		
		pthread_mutex_lock(&data->print_mutex);
		printf("%lld %d is sleeping\n", get_time_ms() - data->start_time, philo->id);
		pthread_mutex_unlock(&data->print_mutex);
		(void) usleep(data->time_to_sleep * 1000);
		
		//philo is done sleeping

		printf("%lld %d is thinking\n", get_time_ms() - data->start_time, philo->id);
	}
	return (NULL);
}
