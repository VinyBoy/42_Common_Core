/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:27:38 by viny              #+#    #+#             */
/*   Updated: 2025/05/22 16:02:52 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*ft_last_env_node(t_env *node)
{
	while (node && node->next)
		node = node->next;
	return (node);
}

void	add_env_node(t_env **lst, char *line_envp)
{
	t_env	*new;

	new = mem_manager(MALLOC, sizeof(t_env), NULL);
	if (!new)
		return ;
	new->env_var = ft_strdup_mem(line_envp);
	new->next = NULL;
	if (!*lst)
		*lst = new;
	else
		ft_last_env_node(*lst)->next = new;
}

void	copy_env(char **envp, t_env **env_copy)
{
	int		i;
	t_env	*lst;

	i = 0;
	lst = *env_copy;
	while (envp[i])
	{
		add_env_node(&lst, envp[i]);
		i++;
	}
	*env_copy = lst;
}

t_env	*get_env(char **envp)
{
	t_env	*env_copy;

	env_copy = NULL;
	copy_env(envp, &env_copy);
	return (env_copy);
}

char	*ft_get_env_var(t_env *env, char *var)
{
	t_env	*cur;
	size_t	len;

	cur = env;
	len = ft_strlen(var);
	while (cur)
	{
		if (!ft_strncmp(cur->env_var, var, len) && cur->env_var[len] == '=')
		{
			return (cur->env_var + len + 1);
		}
		cur = cur->next;
	}
	return (NULL);
}
