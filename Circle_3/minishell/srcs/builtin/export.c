/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:36:10 by oztozdem          #+#    #+#             */
/*   Updated: 2025/05/30 16:01:26 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_env	**list_to_array(t_env *env, int size)
{
	t_env	**array;
	int		i;

	i = 0;
	array = mem_manager(MALLOC, sizeof(t_env *) * (size + 1), NULL);
	if (!array)
		return (NULL);
	while (env)
	{
		array[i] = env;
		i++;
		env = env->next;
	}
	array[i] = NULL;
	return (array);
}

static void	bubble_sort_env(t_env **array, int size)
{
	int		i;
	int		swapped;
	t_env	*tmp;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (i < size - 1)
		{
			if (ft_strcmp(array[i]->env_var, array[i + 1]->env_var) > 0)
			{
				tmp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = tmp;
				swapped = 1;
			}
			i++;
		}
	}
}

static void	print_export(t_env *env)
{
	t_env	**array;
	char	*equal;
	int		size;
	int		i;

	size = count_env(env);
	array = list_to_array(env, size);
	if (!array)
		return ;
	bubble_sort_env(array, size);
	i = 0;
	while (i < size)
	{
		equal = ft_strchr(array[i]->env_var, '=');
		if (equal)
			printf("export %.*s=\"%s\"\n", (int)(equal - array[i]->env_var),
				array[i]->env_var, equal + 1);
		else
			printf("export %s\n", array[i]->env_var);
		i++;
	}
	mem_manager(FREE, 0, array);
}

void	export(char *str, t_env **env)
{
	t_env	*tmp;
	int		len;

	tmp = *env;
	while (tmp)
	{
		len = ft_strchr(str, '=') - str;
		if (!ft_strncmp(tmp->env_var, str, len) && tmp->env_var[len] == '=')
		{
			mem_manager(FREE, 0, tmp->env_var);
			tmp->env_var = ft_strdup_mem(str);
			return ;
		}
		tmp = tmp->next;
	}
	add_env_node(env, str);
}

void	ft_export(char **strs, t_data *data)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	if (strs[0] && !strs[1])
		return (print_export(data->env));
	if (!check_export_event_option(strs, data))
		return ;
	while (strs[++i])
	{
		if (is_valid_export_key(strs[i]))
			export(strs[i], &data->env);
		else
		{
			ft_dprintf(2, "minishell: export: `%s': not a valid identifier\n",
				strs[i]);
			error = 1;
		}
	}
	if (error)
		data->status = 1;
	else
		data->status = 0;
}
