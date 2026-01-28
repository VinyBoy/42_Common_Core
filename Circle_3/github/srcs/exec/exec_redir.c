/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:46:17 by oztozdem          #+#    #+#             */
/*   Updated: 2025/05/27 18:58:25 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_redir(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	handle_redir_out(t_redir_op *op, int *current_out_fd)
{
	int	flags;
	int	fd;

	flags = get_output_flags(op->type);
	close_fd_if_valid(*current_out_fd);
	fd = open(op->target, flags, 0644);
	if (fd == -1)
	{
		write_join_error("minishell: ", op->target,
			": No such file or directory\n");
		return (0);
	}
	*current_out_fd = fd;
	return (1);
}

int	process_single_redir(t_redir_op *op, t_data *data, int *in_fd, int *out_fd)
{
	if (op->type == REDIR_IN)
		return (handle_redir_in(op, in_fd));
	else if (op->type == REDIR_HEREDOC)
		return (handle_heredoc(op, data, in_fd));
	else if (op->type == REDIR_OUT || op->type == REDIR_APPEND)
		return (handle_redir_out(op, out_fd));
	return (1);
}

int	process_all_redirs(t_redir *redir, t_data *data, int *in_fd, int *out_fd)
{
	t_redir_op	*current_op;
	int			result;

	current_op = redir->ops;
	while (current_op)
	{
		result = process_single_redir(current_op, data, in_fd, out_fd);
		if (!result)
		{
			close_fd_if_valid(*in_fd);
			return (0);
		}
		current_op = current_op->next;
	}
	return (1);
}

int	setup_redir(t_redir *redir, t_data *data)
{
	int	current_in_fd;
	int	current_out_fd;
	int	success;

	if (!redir)
		return (0);
	current_in_fd = -1;
	current_out_fd = -1;
	success = process_all_redirs(redir, data, &current_in_fd, &current_out_fd);
	if (!success)
	{
		set_error_state(redir);
		return (0);
	}
	redir->final_in_fd = current_in_fd;
	redir->final_out_fd = current_out_fd;
	return (1);
}
