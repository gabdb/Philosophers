/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:20:47 by gnyssens          #+#    #+#             */
/*   Updated: 2024/11/24 17:05:54 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	my_atoi(const char *str)
{
	int		sign;
	long long	res;
	long long	buff;

	if (!str)
		return (0); //protection rajoutée
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
