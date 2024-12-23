/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:20:47 by gnyssens          #+#    #+#             */
/*   Updated: 2024/12/23 15:19:19 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	my_atoi(const char *str)
{
	int			sign;
	long long	res;
	long long	buff;

	if (!str)
		return (0);
	sign = 1;
	res = 0;
	buff = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign *= (-1);
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str++ - '0';
		if (buff > res && sign > 0)
			return (-1);
		else if (buff > res && sign < 0)
			return (0);
		buff = res;
	}
	return ((long long) sign * res);
}

long long	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(long int time_in_ms, t_data *data)
{
	long int	start_time;

	start_time = 0;
	start_time = get_time_ms();
	while ((get_time_ms() - start_time) < time_in_ms)
	{
		if (data->someone_dead)
			return ;
		usleep(time_in_ms / 10);
	}
}

void	print_mutex_norm(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->print_mutex);
	printf("%lld %d is thinking\n", get_time_ms()
		- data->start_time, philo->id);
	pthread_mutex_unlock(&data->print_mutex);
}
