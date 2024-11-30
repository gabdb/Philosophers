/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:13:09 by gnyssens          #+#    #+#             */
/*   Updated: 2024/11/30 23:43:57 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_meals_eaten(t_data *data)
{
	t_philo		*philos;
	int			nb; //nb of philos

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

//MAUVAISE CONDITION if ()
void	*check_dead(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (all_meals_eaten(data) == 0)
	{
		if (data->someone_dead)
		{
			pthread_mutex_lock(&data->print_mutex);
			printf("%lld %d is dead\n", get_time_ms() - data->start_time, data->dead_id);
			pthread_mutex_unlock(&data->print_mutex);
			return (NULL);
		}
		
		//ft_usleep(1); //jsp si necessaire, pr eviter de surchauffer
	}
	return (NULL);
}

//attention aux multiples break; au milieu des mutex_lock ! p-e pb pr les autres threads si pas unlock !!!
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
		pthread_mutex_lock(&data->death_mutex);
        if (data->someone_dead)
        {
            pthread_mutex_unlock(&data->death_mutex);
            break;
        }
        pthread_mutex_unlock(&data->death_mutex);
		if (get_time_ms() - philo->last_meal_time  + data->time_to_eat > data->time_to_die)
		{
			philo->is_dead = 1;
			pthread_mutex_lock(&data->death_mutex); //p e enlever ce mutex
			data->someone_dead = 1;
			data->dead_id = philo->id;
			pthread_mutex_unlock(&data->death_mutex);
			break;
		}
		if (data->number_meals != -1 && philo->meals_eaten >= data->number_meals)
			break;
		if (philo->id % 2 == 0)
			usleep(50); //sleep 0.5 ms to avoid bug
		lf = philo->left_fork;
		pthread_mutex_lock(data->forks + lf);
		if (data->someone_dead)
			break;
		pthread_mutex_lock(&data->print_mutex);
		printf("%lld %d has taken a fork\n", get_time_ms() - data->start_time, philo->id);
		pthread_mutex_unlock(&data->print_mutex);
		rf = philo->right_fork;
		pthread_mutex_lock(data->forks + rf);
		if (data->someone_dead)
			break;
		pthread_mutex_lock(&data->print_mutex);
		printf("%lld %d has taken a fork\n", get_time_ms() - data->start_time, philo->id);
		pthread_mutex_unlock(&data->print_mutex);
		
		//now that philo has 2 forks, and can eat
		
		philo->is_eating = 1; //SERT A RIEN
		if (data->someone_dead)
			break;
		pthread_mutex_lock(&data->print_mutex);
		printf("%lld %d is eating\n", get_time_ms() - data->start_time, philo->id);
		pthread_mutex_unlock(&data->print_mutex);
		ft_usleep(data->time_to_eat);
		pthread_mutex_unlock(data->forks + lf);
		pthread_mutex_unlock(data->forks + rf);
		philo->is_eating = 0;
		philo->last_meal_time = get_time_ms();
		philo->meals_eaten += 1;
		
		//philo has released forks and will sleep
		
		if (data->someone_dead)
			break;
		pthread_mutex_lock(&data->print_mutex);
		printf("%lld %d is sleeping\n", get_time_ms() - data->start_time, philo->id);
		pthread_mutex_unlock(&data->print_mutex);
		ft_usleep(data->time_to_sleep);
		
		//philo is done sleeping
		if (data->someone_dead)
			break;
		pthread_mutex_lock(&data->print_mutex);
		printf("%lld %d is thinking\n", get_time_ms() - data->start_time, philo->id);
		pthread_mutex_unlock(&data->print_mutex);
	}
	return (NULL);
}
