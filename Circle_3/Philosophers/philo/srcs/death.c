/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:29:16 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/06/17 10:55:34 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	meal_finish(t_data *data)
{
	pthread_mutex_lock(&data->mutexdead);
	data->death = 1;
	pthread_mutex_unlock(&data->mutexdead);
}

void	is_dead(t_philo *philo, t_data *data, int i)
{
	pthread_mutex_lock(&data->mutexdead);
	data->death = 1;
	pthread_mutex_unlock(&data->mutexdead);
	pthread_mutex_lock(&data->print);
	printf("%ld %lu is dead\n", right_time(data->start), philo[i].philo_id);
	pthread_mutex_unlock(&data->print);
}

int	check_death(t_data *data)
{
	int	dead;

	pthread_mutex_lock(&data->mutexdead);
	dead = data->death;
	pthread_mutex_unlock(&data->mutexdead);
	return (dead);
}

int	check_death_meals(t_data *data, t_philo *philo)
{
	unsigned long	i;
	long			time;

	while (!check_death(data))
	{
		i = -1;
		while (++i < data->nb_philo)
		{
			pthread_mutex_lock(&philo[i].meal);
			time = gettime() - philo[i].last_meal;
			pthread_mutex_unlock(&philo[i].meal);
			if (time > data->ttdie)
				return (is_dead(philo, data, i), 1);
			if (data->max_meals != -1)
			{
				pthread_mutex_lock(&data->finish_philo);
				if (data->finish >= data->nb_philo)
					return (leave_meal_finish(data), 1);
				pthread_mutex_unlock(&data->finish_philo);
			}
		}
		usleep(100);
	}
	return (1);
}
