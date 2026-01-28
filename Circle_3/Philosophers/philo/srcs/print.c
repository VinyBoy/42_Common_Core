/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:31:39 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/06/17 11:37:16 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	print_state(t_philo *philo, char *str, int flag)
{
	pthread_mutex_lock(&philo->data->print);
	if (check_death(philo->data))
	{
		pthread_mutex_unlock(&philo->data->print);
		return (1);
	}
	if (flag == 1)
		printf("%s%ld %lu %s\n%s", CYAN, right_time(philo->data->start),
			philo->philo_id, str, RESET);
	if (flag == 2)
		printf("%s%ld %lu %s\n%s", GREEN, right_time(philo->data->start),
			philo->philo_id, str, RESET);
	if (flag == 3)
		printf("%s%ld %lu %s\n%s", YELLOW, right_time(philo->data->start),
			philo->philo_id, str, RESET);
	if (flag == 4)
		printf("%s%ld %lu %s\n%s", PURPLE, right_time(philo->data->start),
			philo->philo_id, str, RESET);
	if (flag == 5)
		printf("%s%ld %lu %s\n%s", RED, right_time(philo->data->start),
			philo->philo_id, str, RESET);
	pthread_mutex_unlock(&philo->data->print);
	return (0);
}

void	one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->mutexrf);
	print_state(philo, "has taken a fork", 1);
	ft_usleep(philo->data, philo->data->ttdie);
	pthread_mutex_unlock(philo->mutexrf);
}

void	leave_meal_finish(t_data *data)
{
	meal_finish(data);
	pthread_mutex_unlock(&data->finish_philo);
}
