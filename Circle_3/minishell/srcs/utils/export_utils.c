/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:57:40 by oztozdem          #+#    #+#             */
/*   Updated: 2025/05/29 20:37:18 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_valid_export_key(const char *str)
{
	int	i;

	if (!str || str[0] == '\0')
		return (0);
	if (str[0] == '=' || ft_isdigit(str[0]))
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

// static int	check_export(char **strs, int *i)
// {
// 	while (strs[*i])
// 	{
// 		if (!is_valid_export_key(strs[*i]))
// 			return (0);
// 		(*i)++;
// 	}
// 	return (1);
// }

static int	check_event(char **strs, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (strs[i])
	{
		j = 0;
		while (strs[i][j])
		{
			if (strs[i][j] == '!')
			{
				data->status = 0;
				return (ft_dprintf(2, "minishell: %s: event not found\n",
						strs[i] + j), 0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	check_export_event_option(char **strs, t_data *data)
{
	if (strs[1][0] == '-')
	{
		data->status = 2;
		return (ft_dprintf(2, "minishell: export: -%c: invalid option\n",
				strs[1][1]), 0);
	}
	if (!check_event(strs, data))
		return (0);
	return (1);
}
