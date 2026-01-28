/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:01:09 by oztozdem          #+#    #+#             */
/*   Updated: 2025/05/28 12:28:57 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	cmd_here_doc(t_exec *exec, t_data *data, int i, int *hd_idx)
{
	t_redir_op	*current;

	if (exec->redir && exec->redir[i] && exec->redir[i]->ops)
	{
		current = exec->redir[i]->ops;
		while (current)
		{
			if (current->type == REDIR_HEREDOC)
			{
				current->here_doc_index = *hd_idx;
				if (!process_single_here_doc(data, current->target, *hd_idx))
					return (0);
				(*hd_idx)++;
			}
			current = current->next;
		}
	}
	return (1);
}

int	setup_here_doc(t_exec *exec, t_data *data)
{
	int			i;
	int			hd_idx;
	int			count;

	count = count_here_doc(exec);
	if (count == 0)
		return (1);
	if (!allocate_here_doc(data, count))
		return (0);
	hd_idx = 0;
	i = -1;
	while (++i < exec->cmd_count)
		if (!cmd_here_doc(exec, data, i, &hd_idx))
			return (close_here_doc(data), 0);
	return (1);
}

int	find_here_doc_index(t_data *data, char *delim)
{
	int	i;

	i = -1;
	while (++i < data->here_count)
	{
		if (!ft_strcmp(data->here[i].delim, delim))
			return (i);
	}
	return (-1);
}

void	close_here_doc(t_data *data)
{
	int	i;

	if (!data || !data->here)
		return ;
	i = -1;
	while (++i < data->here_count)
	{
		if (data->here[i].pipefd[0] >= 0)
		{
			close(data->here[i].pipefd[0]);
			data->here[i].pipefd[0] = -1;
		}
		if (data->here[i].pipefd[1] >= 0)
		{
			close(data->here[i].pipefd[1]);
			data->here[i].pipefd[1] = -1;
		}
		if (data->here[i].delim)
			mem_manager(FREE, 0, data->here[i].delim);
	}
	mem_manager(FREE, 0, data->here);
	data->here = NULL;
	data->here_count = 0;
}
