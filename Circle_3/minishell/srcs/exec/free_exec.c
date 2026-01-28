/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:48:28 by oztozdem          #+#    #+#             */
/*   Updated: 2025/05/30 16:03:35 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_exec(t_exec *exec)
{
	if (exec)
	{
		if (exec->path)
			free_split(exec->path);
		if (exec->envp)
			free_split(exec->envp);
		if (exec->pids)
			mem_manager(FREE, 0, exec->pids);
		free_redirections(exec);
		free_pipes(exec);
		mem_manager(FREE, 0, exec);
	}
}

void	free_single_redir(t_redir *redir)
{
	t_redir_op	*current_op;
	t_redir_op	*next_op;

	if (!redir)
		return ;
	close_redir(redir);
	current_op = redir->ops;
	while (current_op)
	{
		next_op = current_op->next;
		if (current_op->target)
			mem_manager(FREE, 0, current_op->target);
		mem_manager(FREE, 0, current_op);
		current_op = next_op;
	}
	mem_manager(FREE, 0, redir);
}

void	free_redirections(t_exec *exec)
{
	int	i;

	if (!exec || !exec->redir)
		return ;
	i = -1;
	while (++i < exec->cmd_count)
		free_single_redir(exec->redir[i]);
	mem_manager(FREE, 0, exec->redir);
	exec->redir = NULL;
}

void	free_pipes(t_exec *exec)
{
	int	i;

	if (exec->pipe_fds)
	{
		i = -1;
		while (++i < exec->cmd_count - 1)
		{
			if (exec->pipe_fds[i])
				mem_manager(FREE, 0, exec->pipe_fds[i]);
		}
		mem_manager(FREE, 0, exec->pipe_fds);
		exec->pipe_fds = NULL;
	}
}

void	handle_signals_in_child(void)
{
	signal(SIGINT, sig_int_child);
	signal(SIGQUIT, sig_quit_child);
}
