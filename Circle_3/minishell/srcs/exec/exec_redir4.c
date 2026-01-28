/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:57:53 by oztozdem          #+#    #+#             */
/*   Updated: 2025/05/28 14:01:38 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_fd_if_valid(int fd)
{
	if (fd != -1)
		close(fd);
}

void	set_error_state(t_redir *redir)
{
	redir->final_in_fd = -1;
	redir->final_out_fd = -1;
}

int	handle_redir_in(t_redir_op *op, int *current_in_fd)
{
	int	fd;

	close_fd_if_valid(*current_in_fd);
	fd = open(op->target, O_RDONLY);
	if (fd == -1)
	{
		write_join_error("minishell: ", op->target,
			": No such file or directory\n");
		return (0);
	}
	*current_in_fd = fd;
	return (1);
}

int	handle_heredoc(t_redir_op *op, t_data *data, int *current_in_fd)
{
	int	hd_idx;
	int	fd;

	close_fd_if_valid(*current_in_fd);
	hd_idx = op->here_doc_index;
	if (hd_idx == -1)
	{
		write_join_error("minishell: here_doc: ", op->target,
			": here_doc not found\n");
		return (0);
	}
	fd = dup(data->here[hd_idx].pipefd[0]);
	if (fd == -1)
	{
		perror("minishell: dup");
		return (0);
	}
	*current_in_fd = fd;
	return (1);
}

int	get_output_flags(int redir_type)
{
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (redir_type == REDIR_OUT)
		flags |= O_TRUNC;
	else
		flags |= O_APPEND;
	return (flags);
}
