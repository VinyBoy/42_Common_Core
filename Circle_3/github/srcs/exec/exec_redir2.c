/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:57:10 by oztozdem          #+#    #+#             */
/*   Updated: 2025/05/27 19:08:03 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	alloc_redir(t_exec *exec, t_cmd *cmd)
{
	int	i;

	exec->redir = mem_manager(MALLOC,
			sizeof(t_redir *) * exec->cmd_count, NULL);
	if (!exec->redir)
		return (0);
	i = -1;
	while (++i < exec->cmd_count)
	{
		exec->redir[i] = mem_manager(MALLOC, sizeof(t_redir), NULL);
		if (!exec->redir[i])
			return (0);
		init_cmd_redir(exec->redir[i], cmd, i);
	}
	return (1);
}

int	process_cmd_redir(t_exec *exec, t_cmd *cmd)
{
	if (!alloc_redir(exec, cmd))
		return (0);
	return (1);
}

void	apply_redir(t_exec *exec, t_data *data, int cmd_index)
{
	t_redir	*redir;

	redir = exec->redir[cmd_index];
	if (redir->final_in_fd != -1)
		dup_pipe_end(data, redir->final_in_fd, STDIN_FILENO, exec);
	if (redir->final_out_fd != -1)
		dup_pipe_end(data, redir->final_out_fd, STDOUT_FILENO, exec);
}

void	close_redir(t_redir *redir)
{
	if (!redir)
		return ;
	if (redir->final_in_fd >= 0 && redir->final_in_fd != STDIN_FILENO)
	{
		if (close(redir->final_in_fd) == -1)
			perror("minishell: close final_in_fd");
		redir->final_in_fd = -1;
	}
	if (redir->final_out_fd >= 0 && redir->final_out_fd != STDOUT_FILENO)
	{
		if (close(redir->final_out_fd) == -1)
			perror("minishell: close final_out_fd");
		redir->final_out_fd = -1;
	}
}

void	close_all_redir(t_exec *exec)
{
	int	i;

	i = -1;
	while (++i < exec->cmd_count)
		if (exec->redir[i])
			close_redir(exec->redir[i]);
}
