/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:55:41 by gnyssens          #+#    #+#             */
/*   Updated: 2024/11/26 18:50:04 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <time.h>
# include <sys/time.h>
# include <sys/types.h>

struct s_philo;

typedef struct s_data
{
	struct s_philo			*philos;
	pthread_mutex_t	*forks;

	int				number_philos;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				number_meals; // (truc optionnel)

	long long		start_time;
	int				someone_dead;
	
	pthread_mutex_t	print_mutex; //pr pas qu'ils ne printent en mm temps
}				t_data;

typedef struct s_philo
{
	int				id; //ranking them
	pthread_t		thread;

	int				left_fork;
	int				right_fork;
	int				is_eating;
	long long		last_meal_time;
	int				meals;

	t_data			*data;

}               t_philo;

// PARSING
int	parsing(int ac, char **av);

//INIT
int	initialize_data(int ac, char **av, t_data *data);
void	init_philo(t_data *data);

//FREE
void	big_free(pthread_mutex_t *forks, t_philo *philos);
int		free_and_destroy(t_data *data);

// UTILS
long long	my_atoi(const char *str);
long long 	get_time_ms(void);

#endif