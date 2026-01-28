/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:52:17 by oztozdem          #+#    #+#             */
/*   Updated: 2025/05/30 16:03:20 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_single_builtin(t_exec *exec, t_data *data, t_cmd *cmd)
{
	if (!setup_redir(exec->redir[0], data))
		return (1);
	exec->line = cmd->args;
	if (!exec->line)
		return (1);
	if (!exec->line[0])
	{
		mem_manager(FREE, 0, exec->line);
		exec->line = NULL;
		return (0);
	}
	if (is_builtin(exec->line[0]))
		return (handle_builtin_redir(exec, data), data->status);
	exec->line = NULL;
	return (-1);
}

int	exec_env(t_exec *exec, t_data *data)
{
	char	*path_env;

	exec->envp = env_to_array(data->env);
	if (!exec->envp)
		return (0);
	path_env = ft_get_env_var(data->env, "PATH");
	if (path_env)
	{
		exec->path = ft_split_mem(path_env, ':');
		if (!exec->path)
			return (0);
	}
	else
	{
		exec->path = NULL;
		exec->no_path = 1;
	}
	return (1);
}

int	create_pipes(t_exec *exec)
{
	int	i;

	if (exec->cmd_count <= 1)
		return (1);
	exec->pipe_fds = mem_manager(MALLOC, sizeof(int *) * (exec->cmd_count - 1),
			NULL);
	if (!exec->pipe_fds)
		return (0);
	i = -1;
	while (++i < exec->cmd_count - 1)
	{
		exec->pipe_fds[i] = mem_manager(MALLOC, sizeof(int) * 2, NULL);
		if (!exec->pipe_fds[i])
			return (0);
		if (pipe(exec->pipe_fds[i]) == -1)
			return (perror("minishell: pipe"), 0);
	}
	return (1);
}

int	pids_alloc(t_exec *exec)
{
	exec->pids = mem_manager(MALLOC, sizeof(pid_t) * exec->cmd_count, NULL);
	if (!exec->pids)
		return (0);
	return (1);
}

void	setup_pipes(t_data *data, t_exec *exec, int cmd_index)
{
	int	i;

	if (cmd_index > 0)
		dup_pipe_end(data, exec->pipe_fds[cmd_index - 1][0], STDIN_FILENO,
			exec);
	if (cmd_index < exec->cmd_count - 1)
		dup_pipe_end(data, exec->pipe_fds[cmd_index][1], STDOUT_FILENO, exec);
	i = -1;
	while (++i < exec->cmd_count - 1)
	{
		close(exec->pipe_fds[i][0]);
		close(exec->pipe_fds[i][1]);
	}
}
