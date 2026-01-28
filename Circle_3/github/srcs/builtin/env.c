/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:05:02 by oztozdem          #+#    #+#             */
/*   Updated: 2025/05/30 16:00:50 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env(t_env *env, t_data *data)
{
	while (env)
	{
		if (ft_strchr(env->env_var, '='))
			printf("%s\n", env->env_var);
		env = env->next;
	}
	data->status = 0;
}
