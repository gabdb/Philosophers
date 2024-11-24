/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:55:41 by gnyssens          #+#    #+#             */
/*   Updated: 2024/11/24 17:51:59 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//ifndef etc.

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

typedef struct s_philo
{
	int				id; //ranking them
	pthread_t		thread;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
	
	int				meals;
}               t_philo;

typedef struct s_data
{
	pthread_t		*philos;
	pthread_mutex_t	*forks;

	int				number_philos;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				number_meals; // (truc optionnel)
	
	pthread_mutex_t	print_mutex; //pr pas qu'ils ne printent en mm temps
}				t_data;

// UTILS
long long	my_atoi(const char *str);

// PARSING
int	parsing(int ac, char **av);

//FREE
void	big_free(pthread_mutex_t *forks, pthread_t *philos);
