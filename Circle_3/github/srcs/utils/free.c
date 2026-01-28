/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:15:10 by oztozdem          #+#    #+#             */
/*   Updated: 2025/05/21 16:25:40 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* Free un t_env */
void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		mem_manager(FREE, 0, tmp->env_var);
		mem_manager(FREE, 0, tmp);
	}
	env = NULL;
}

/* Free un split */
void	free_split(char **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return ;
	while (strs[i])
	{
		mem_manager(FREE, 0, strs[i]);
		i++;
	}
	mem_manager(FREE, 0, strs);
}

/* Free une structure t_data * */
void	free_data(t_data *data)
{
	if (data)
	{
		if (data->env)
			free_env_list(data->env);
		if (data->input)
			mem_manager(FREE, 0, data->input);
		if (data->here)
			close_here_doc(data);
		data->input = NULL;
		mem_manager(FREE, 0, data);
		data = NULL;
	}
}
