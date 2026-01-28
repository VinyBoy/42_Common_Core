/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:58:52 by oztozdem          #+#    #+#             */
/*   Updated: 2025/05/30 16:03:02 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_cmd_path(t_exec *exec)
{
	char	*tmp;
	char	*cmd_path;
	int		i;

	if (!exec->line || !exec->line[0])
		return (NULL);
	if (ft_strchr(exec->line[0], '/'))
		return (ft_strdup_mem(exec->line[0]));
	if (!exec->path)
	{
		exec->no_path = 1;
		return (NULL);
	}
	i = 0;
	while (exec->path && exec->path[i])
	{
		tmp = ft_strjoin_mem(exec->path[i], "/");
		cmd_path = ft_strjoin_mem(tmp, exec->line[0]);
		mem_manager(FREE, 0, tmp);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		mem_manager(FREE, 0, cmd_path);
		i++;
	}
	return (NULL);
}

int	check_path_permissions(char *cmd_path)
{
	struct stat	sb;

	if (stat(cmd_path, &sb) == 0)
	{
		if (S_ISDIR(sb.st_mode))
		{
			write_join_error("minishell: ", cmd_path, ": Is a directory\n");
			return (126);
		}
		if (access(cmd_path, X_OK) != 0)
		{
			write_join_error("minishell: ", cmd_path, ": Permission denied\n");
			return (126);
		}
	}
	else
	{
		write_join_error("minishell: ", cmd_path,
			": No such file or directory\n");
		return (127);
	}
	return (0);
}

int	handle_cmd_error(char *cmd_path, t_exec *exec)
{
	int	n;

	if (!cmd_path)
	{
		if (exec->no_path)
			write_join_error("minishell: ", exec->line[0],
				": No such file or directory\n");
		else
			write_join_error("minishell: ", exec->line[0],
				": command not found\n");
		return (127);
	}
	n = check_path_permissions(cmd_path);
	if (n != 0)
		return (mem_manager(FREE, 0, cmd_path), n);
	return (0);
}

int	handle_builtin(t_exec *exec, t_data *data)
{
	int	exit_status;

	exit_status = 0;
	if (is_builtin(exec->line[0]))
	{
		ft_builtin(exec, data, -1, -1);
		exit_status = data->status;
		mem_manager(FREEALL, 0, NULL);
		exit(exit_status);
	}
	return (0);
}

void	close_pipes(t_exec *exec)
{
	int	i;

	if (exec->cmd_count <= 1)
		return ;
	i = -1;
	while (++i < exec->cmd_count - 1)
	{
		close(exec->pipe_fds[i][0]);
		close(exec->pipe_fds[i][1]);
	}
}
