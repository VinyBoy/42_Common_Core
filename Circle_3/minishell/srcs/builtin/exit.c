/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:27:40 by oztozdem          #+#    #+#             */
/*   Updated: 2025/05/30 16:10:28 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static long long	ft_atoll(char *str, int *error)
{
	unsigned long long	result;
	int					i;
	int					j;
	int					sign;

	sign = 1;
	result = 0;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	j = i;
	while (str[i] >= '0' && str[i] <= '9')
		result = result * 10 + str[i++] - '0';
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] != '\0' || i == j || i - j > 20)
		*error = 1;
	else if (sign == -1 && result > (unsigned long long)LONG_MAX + 1)
		*error = 1;
	else if (sign == 1 && result > (unsigned long long)LONG_MAX)
		*error = 1;
	return ((result * sign) % 256);
}

static void	launch_exit(t_data *data, t_exec *exec, int *error, int *argc)
{
	long long	nb;

	if (*argc >= 2 && exec->line[1][0])
	{
		nb = ft_atoll(exec->line[1], error);
		if (*error)
		{
			ft_dprintf(2, "minishell: exit: %s: numeric argument required\n",
				exec->line[1]);
			mem_manager(FREEALL, 0, NULL);
			exit(2);
		}
		if (*argc > 2)
		{
			ft_dprintf(2, "minishell: exit: too many arguments\n");
			data->status = 1;
			return ;
		}
		mem_manager(FREEALL, 0, NULL);
		exit((unsigned char)nb);
	}
}

void	ft_exit(t_exec *exec, t_data *data)
{
	int			error;
	int			argc;

	error = 0;
	argc = count_args(exec->line);
	write(1, "exit\n", 5);
	if (argc == 1)
	{	
		mem_manager(FREEALL, 0, NULL);
		exit(0);
	}
	launch_exit(data, exec, &error, &argc);
}
