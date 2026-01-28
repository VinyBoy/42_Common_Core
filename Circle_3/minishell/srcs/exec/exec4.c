/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:05:06 by oztozdem          #+#    #+#             */
/*   Updated: 2025/05/27 19:59:45 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	create_child_processes(t_exec *exec, t_data *data, t_cmd *cmd)
{
	int	i;

	i = -1;
	while (++i < exec->cmd_count)
	{
		exec->pids[i] = fork();
		if (exec->pids[i] < 0)
			return (perror("minishell: fork"), 0);
		else if (exec->pids[i] == 0)
		{
			handle_signals_in_child();
			if (!setup_redir(exec->redir[i], data))
			{
				mem_manager(FREEALL, 0, NULL);
				exit(1);
			}
			exec_cmd(exec, data, i, cmd);
			exit(1);
		}
	}
	return (1);
}

void	close_heredoc_pipes(t_data *data)
{
	int	k;

	if (!data || !data->here)
		return ;
	k = -1;
	while (++k < data->here_count)
	{
		if (data->here[k].pipefd[0] >= 0)
			close(data->here[k].pipefd[0]);
	}
}

t_cmd	*find_current_cmd(t_cmd *cmd, int cmd_index)
{
	t_cmd	*current;
	int		k;

	current = cmd;
	k = -1;
	while (++k < cmd_index && current)
		current = current->next;
	return (current);
}

void	validate_cmd_args(t_cmd *current, t_exec *exec)
{
	if (!current)
	{
		mem_manager(FREEALL, 0, NULL);
		exit(127);
	}
	exec->line = current->args;
	if (!exec->line)
	{
		mem_manager(FREEALL, 0, NULL);
		exit(1);
	}
}

void	execute_external_cmd(t_exec *exec, t_data *data)
{
	char	*cmd_path;
	int		error;

	cmd_path = get_cmd_path(exec);
	error = handle_cmd_error(cmd_path, exec);
	if (error)
	{
		mem_manager(FREEALL, 0, NULL);
		exit(error);
	}
	run_exec(exec, data, cmd_path);
}
