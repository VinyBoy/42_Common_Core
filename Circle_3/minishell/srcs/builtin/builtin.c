/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:49:36 by oztozdem          #+#    #+#             */
/*   Updated: 2025/04/09 12:49:36 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin(char *str)
{
	if ((!ft_strcmp(str, "pwd"))
		|| (!ft_strcmp(str, "cd"))
		|| (!ft_strcmp(str, "echo"))
		|| (!ft_strcmp(str, "env"))
		|| (!ft_strcmp(str, "exit"))
		|| (!ft_strcmp(str, "export"))
		|| (!ft_strcmp(str, "unset")))
		return (1);
	return (0);
}

void	ft_builtin(t_exec *exec, t_data *data, int stdin_save, int stdout_save)
{
	if (!ft_strcmp(exec->line[0], "pwd"))
		ft_pwd(exec->line, data);
	else if (!ft_strcmp(exec->line[0], "cd"))
		ft_cd(exec->line, data);
	else if (!ft_strcmp(exec->line[0], "echo"))
		ft_echo(exec->line, data);
	else if (!ft_strcmp(exec->line[0], "env"))
		ft_env(data->env, data);
	else if (!ft_strcmp(exec->line[0], "exit"))
	{
		if (stdin_save != -1)
			close(stdin_save);
		if (stdout_save != -1)
			close(stdout_save);
		ft_exit(exec, data);
	}
	else if (!ft_strcmp(exec->line[0], "export"))
		ft_export(exec->line, data);
	else if (!ft_strcmp(exec->line[0], "unset"))
		ft_unset(exec->line, data);
}
