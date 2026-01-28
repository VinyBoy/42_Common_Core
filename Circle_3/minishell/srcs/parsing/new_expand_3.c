/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_expand_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:59:42 by oztozdem          #+#    #+#             */
/*   Updated: 2025/05/30 23:08:14 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_dollar(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	handle_dollar_double_quote(char *new_input, char *input, t_data *data,
		int *j)
{
	int	start_j;

	start_j = 0;
	data->i++;
	while (input[data->i] && input[data->i] != '"')
	{
		new_input[*j + start_j++] = input[data->i];
		data->i++;
	}
	if (check_dollar(input + data->i))
		return (start_j);
	while (input[data->i] && input[data->i] == '"')
	{
		data->i++;
		while (input[data->i] && input[data->i] != '"')
		{
			new_input[*j + start_j++] = input[data->i];
			data->i++;
		}
		if (input[data->i] == '"')
			data->i++;
	}
	data->i--;
	return (start_j);
}

int	handle_dollar_single_quote(char *new_input, char *input, t_data *data,
		int *j)
{
	int	start_j;

	start_j = 0;
	data->i++;
	while (input[data->i] && input[data->i] != '\'')
	{
		new_input[*j + start_j++] = input[data->i];
		data->i++;
	}
	if (check_dollar(input + data->i))
		return (start_j);
	while (input[data->i] && input[data->i] == '\'')
	{
		data->i++;
		while (input[data->i] && input[data->i] != '\'')
		{
			new_input[*j + start_j++] = input[data->i];
			data->i++;
		}
		if (input[data->i] == '\'')
			data->i++;
	}
	data->i--;
	return (start_j);
}
