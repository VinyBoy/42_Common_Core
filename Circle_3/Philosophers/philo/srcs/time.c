/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:32:00 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/06/17 10:58:29 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long	gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long	right_time(long delay)
{
	return (gettime() - delay);
}

void	set_start_time(t_data *data)
{
	size_t	i;

	data->start = gettime();
	i = -1;
	while (++i < data->nb_philo)
		data->philo[i].last_meal = gettime();
}

int	thinking(t_philo *philo)
{
	return (print_state(philo, "is thinking", 4));
}
