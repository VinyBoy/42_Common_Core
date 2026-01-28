/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:28:34 by oztozdem          #+#    #+#             */
/*   Updated: 2025/05/30 16:08:28 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

#include "../../include/minishell.h"

t_redir_type	op_type(t_tokens type)
{
	if (type == LESS)
		return (REDIR_IN);
	else if (type == LESS_LESS)
		return (REDIR_HEREDOC);
	else if (type == GREAT)
		return (REDIR_OUT);
	else if (type == GREAT_GREAT)
		return (REDIR_APPEND);
	return (-1);
}

static t_redir_op	*create_redir_op(t_redirs *redirs)
{
	t_redir_op	*new_op;

	new_op = mem_manager(MALLOC, sizeof(t_redir_op), NULL);
	new_op->type = op_type(redirs->type);
	new_op->target = redirs->file;
	new_op->here_doc_index = -1;
	new_op->next = NULL;
	return (new_op);
}

t_redir_op	*redirs_to_ops(t_redirs *redirs)
{
	t_redir_op	*new_op;
	t_redir_op	*current;
	t_redir_op	*head;

	current = NULL;
	head = NULL;
	while (redirs)
	{
		new_op = create_redir_op(redirs);
		if (!current)
		{
			current = new_op;
			head = current;
		}
		else
		{
			current->next = new_op;
			current = current->next;
		}
		redirs = redirs->next;
	}
	return (head);
}

void	init_cmd_redir(t_redir *redir, t_cmd *cmd, int i)
{
	if (!redir)
		return ;
	while (i-- && cmd)
		cmd = cmd->next;
	redir->ops = redirs_to_ops(cmd->redirs);
	redir->final_in_fd = -1;
	redir->final_out_fd = -1;
}
