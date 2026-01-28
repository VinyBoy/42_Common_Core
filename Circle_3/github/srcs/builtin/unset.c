/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 07:58:18 by oztozdem          #+#    #+#             */
/*   Updated: 2025/05/30 16:01:37 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_unset(char *str)
{
	int	i;

	i = 0;
	if (str[0] >= '0' && str[0] <= '9')
		return (0);
	while (str[i])
	{
		if ((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] >= '0' && str[i] <= '9')
			|| str[i] == '_')
			i++;
		else
			return (0);
	}
	return (1);
}

static void	remove_env_node(t_data *data, char *str)
{
	t_env	*tmp;
	t_env	*save;

	tmp = data->env;
	save = NULL;
	while (tmp)
	{
		if (!ft_strncmp(tmp->env_var, str, ft_strlen(str)))
		{
			if (!save)
				data->env = tmp->next;
			else
				save->next = tmp->next;
			mem_manager(FREE, 0, tmp->env_var);
			mem_manager(FREE, 0, tmp);
			return ;
		}
		save = tmp;
		tmp = tmp->next;
	}
}

void	ft_unset(char **strs, t_data *data)
{
	int		i;

	i = 1;
	while (strs[i])
	{
		if (!check_unset(strs[i]))
		{
			ft_dprintf(2, "minishell: unset: '%s': not a valid identifier\n",
				strs[1]);
		}
		else
			remove_env_node(data, strs[i]);
		i++;
	}
}
