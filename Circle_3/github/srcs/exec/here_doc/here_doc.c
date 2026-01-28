/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 12:15:33 by oztozdem          #+#    #+#             */
/*   Updated: 2025/05/28 21:09:17 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	init_here_doc(t_data *data)
{
	data->here_count = 0;
	data->here = NULL;
}

int	count_here_doc(t_exec *exec)
{
	int			count;
	int			i;
	t_redir_op	*current;

	i = -1;
	count = 0;
	while (++i < exec->cmd_count)
	{
		if (exec->redir && exec->redir[i] && exec->redir[i]->ops)
		{
			current = exec->redir[i]->ops;
			while (current)
			{
				if (current->type == REDIR_HEREDOC)
					count++;
				current = current->next;
			}
		}
	}
	return (count);
}

int	allocate_here_doc(t_data *data, int count)
{
	int	k;

	if (count == 0)
		return (1);
	data->here_count = count;
	data->here = mem_manager(MALLOC, sizeof(t_here_doc) * count, NULL);
	if (!data->here)
		return (0);
	k = -1;
	while (++k < count)
	{
		data->here[k].pipefd[0] = -1;
		data->here[k].pipefd[1] = -1;
		data->here[k].delim = NULL;
	}
	return (1);
}

int	is_quoted_delim(char *delim)
{
	size_t	len;

	if (!delim || !delim[0])
		return (0);
	if ((delim[0] == '\'' || delim[0] == '"'))
	{
		len = 0;
		while (delim[len])
			len++;
		if (len >= 2 && delim[len - 1] == delim[0])
			return (1);
	}
	return (0);
}
