/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:51:54 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/05/30 19:06:44 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	run_exec(t_exec *exec, t_data *data, char *cmd_path)
{
	char	**clean_exec;

	(void)data;
	clean_exec = line_clean(exec->line);
	execve(cmd_path, clean_exec, exec->envp);
	mem_manager(FREEALL, 0, NULL);
	perror("minishell: execve");
	exit(127);
}

void	exec_cmd(t_exec *exec, t_data *data, int cmd_index, t_cmd *cmd)
{
	t_cmd	*current;

	if (exec->cmd_count > 1)
		setup_pipes(data, exec, cmd_index);
	apply_redir(exec, data, cmd_index);
	close_heredoc_pipes(data);
	current = find_current_cmd(cmd, cmd_index);
	validate_cmd_args(current, exec);
	if (handle_builtin(exec, data))
		return ;
	execute_external_cmd(exec, data);
}

static int	handle_single_builtin_cmd(t_exec *exec, t_data *data, t_cmd *cmd)
{
	int	builtin_status;

	builtin_status = handle_single_builtin(exec, data, cmd);
	close_all_redir(exec);
	if (builtin_status >= 0)
	{
		exec->line = NULL;
		close_here_doc(data);
		return (builtin_status);
	}
	return (-1);
}

int	handle_commands(t_exec *exec, t_data *data, t_cmd *cmd)
{
	int	builtin_status;

	if (!process_cmd_redir(exec, cmd))
		return (1);
	if (!setup_here_doc(exec, data))
		return (close_here_doc(data), data->status);
	if (exec->cmd_count == 1)
	{
		builtin_status = handle_single_builtin_cmd(exec, data, cmd);
		if (builtin_status >= 0)
			return (builtin_status);
	}
	if (!exec_env(exec, data))
		return (close_here_doc(data), 1);
	if (!create_pipes(exec))
		return (close_here_doc(data), 1);
	if (!pids_alloc(exec))
		return (close_here_doc(data), 1);
	if (!create_child_processes(exec, data, cmd))
		return (close_pipes(exec), close_all_redir(exec), close_here_doc(data),
			1);
	close_pipes(exec);
	close_all_redir(exec);
	close_here_doc(data);
	return (wait_for_children(exec));
}

int	ft_exec(t_data *data, t_cmd *cmd)
{
	t_exec	*exec;

	if (cmd->args && cmd->args[0] && cmd->args[0][0] == '\0')
		return (0);
	exec = mem_manager(MALLOC, sizeof(t_exec), NULL);
	if (!exec)
		return (1);
	init_exec(exec);
	exec->cmd_count = count_cmds(cmd);
	data->status = handle_commands(exec, data, cmd);
	return (free_exec(exec), data->status);
}
