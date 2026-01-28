/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_here.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:05:49 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/05/28 12:58:55 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*do_expand_here(char *input, t_data *data)
{
	char	*new_input;
	int		j;

	data->i = -1;
	j = 0;
	new_input = malloc(sizeof(char) * 100000);
	if (!new_input)
		return (NULL);
	while (input[++data->i])
	{
		if (input[data->i] == '$' && !ft_iswspaces(input[data->i + 1])
			&& input[data->i + 1] != '\0')
			j += expand_from_dollar(new_input, input, data, &j);
		else
		{
			new_input[j] = input[data->i];
			j++;
		}
	}
	new_input[j] = '\0';
	mem_manager(FREE, 0, input);
	return (new_input);
}
