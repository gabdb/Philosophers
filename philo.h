/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:55:41 by gnyssens          #+#    #+#             */
/*   Updated: 2024/11/30 23:43:40 by gnyssens         ###   ########.fr       */
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

struct s_data;

typedef struct s_philo
{
	int				id; //ranking them
	pthread_t		thread;

	int				left_fork;
	int				right_fork;
	int				is_eating;
	long long		last_meal_time;
	int				meals_eaten;
	int				is_dead;

	struct s_data			*data;

}               t_philo;

typedef struct s_data
{
	t_philo			*philos;
	pthread_mutex_t	*forks;

	int				number_philos;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				number_meals; // (truc optionnel)

	long long		start_time;
	int				someone_dead;
	int				dead_id;
	
	pthread_mutex_t	print_mutex; //pr pas qu'ils ne printent en mm temps
	pthread_mutex_t	death_mutex; //jsp trop
}				t_data;

// PARSING
int	parsing(int ac, char **av);

//INIT
int	initialize_data(char **av, t_data *data);
void	init_philo(t_data *data);

//FREE
void	big_free(pthread_mutex_t *forks, t_philo *philos);
int		free_and_destroy(t_data *data);

// UTILS
long long	my_atoi(const char *str);
long long 	get_time_ms(void);
void	ft_usleep(long int time_in_ms);

//ROUTINE
void	*routine(void *arg);
void	*check_dead(void *arg);
int	all_meals_eaten(t_data *data);

#endif