/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:28:20 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/06/17 10:57:37 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	left_right(t_philo *philo)
{
	pthread_mutex_lock(philo->mutexlf);
	if (check_death(philo->data))
	{
		pthread_mutex_unlock(philo->mutexlf);
		return (1);
	}
	if (print_state(philo, "has taken a fork", 1))
	{
		pthread_mutex_unlock(philo->mutexlf);
		return (1);
	}
	pthread_mutex_lock(philo->mutexrf);
	if (check_death(philo->data))
	{
		pthread_mutex_unlock(philo->mutexlf);
		pthread_mutex_unlock(philo->mutexrf);
		return (1);
	}
	if (print_state(philo, "has taken a fork", 1))
	{
		pthread_mutex_unlock(philo->mutexlf);
		pthread_mutex_unlock(philo->mutexrf);
		return (1);
	}
	return (0);
}

int	right_left(t_philo *philo)
{
	pthread_mutex_lock(philo->mutexrf);
	if (check_death(philo->data))
	{
		pthread_mutex_unlock(philo->mutexrf);
		return (1);
	}
	if (print_state(philo, "has taken a fork", 1))
	{
		pthread_mutex_unlock(philo->mutexrf);
		return (1);
	}
	pthread_mutex_lock(philo->mutexlf);
	if (check_death(philo->data))
	{
		pthread_mutex_unlock(philo->mutexrf);
		pthread_mutex_unlock(philo->mutexlf);
		return (1);
	}
	if (print_state(philo, "has taken a fork", 1))
	{
		pthread_mutex_unlock(philo->mutexrf);
		pthread_mutex_unlock(philo->mutexlf);
		return (1);
	}
	return (0);
}

int	take_forks(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		if (left_right(philo))
			return (1);
	}
	else
	{
		if (right_left(philo))
			return (1);
	}
	if (check_death(philo->data))
	{
		pthread_mutex_unlock(philo->mutexlf);
		pthread_mutex_unlock(philo->mutexrf);
		return (1);
	}
	return (print_state(philo, "is eating", 2));
}

int	resting(t_data *data, t_philo *philo)
{
	if (print_state(philo, "is sleeping", 3))
		return (1);
	if (ft_usleep(data, data->ttsleep))
		return (1);
	return (0);
}

int	eat(t_data *data, t_philo *philo)
{
	if (take_forks(philo))
		return (1);
	pthread_mutex_lock(&philo->meal);
	philo->last_meal = gettime();
	pthread_mutex_unlock(&philo->meal);
	if (ft_usleep(data, data->tteat))
	{
		pthread_mutex_unlock(philo->mutexlf);
		pthread_mutex_unlock(philo->mutexrf);
		return (1);
	}
	pthread_mutex_unlock(philo->mutexlf);
	pthread_mutex_unlock(philo->mutexrf);
	philo->nb_meals++;
	if (data->max_meals != -1 && philo->nb_meals == data->max_meals)
	{
		pthread_mutex_lock(&data->finish_philo);
		data->finish++;
		pthread_mutex_unlock(&data->finish_philo);
		return (1);
	}
	return (0);
}
