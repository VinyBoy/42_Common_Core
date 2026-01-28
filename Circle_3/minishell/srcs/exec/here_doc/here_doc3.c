/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:59:28 by oztozdem          #+#    #+#             */
/*   Updated: 2025/05/28 13:59:45 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	setup_heredoc_pipe(t_data *data, int index)
{
	if (pipe(data->here[index].pipefd) == -1)
	{
		perror("minishell: pipe");
		return (0);
	}
	return (1);
}

static int	duplicate_delimiter(t_data *data, char *delim, int index)
{
	data->here[index].delim = ft_strdup_mem(delim);
	if (!data->here[index].delim)
	{
		close(data->here[index].pipefd[0]);
		close(data->here[index].pipefd[1]);
		return (0);
	}
	return (1);
}

static pid_t	create_heredoc_child(t_data *data, char *delim, int index)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		close(data->here[index].pipefd[0]);
		close(data->here[index].pipefd[1]);
		return (-1);
	}
	if (pid == 0)
		handle_here_doc_child(delim, data->here[index].pipefd, data);
	return (pid);
}

static int	wait_heredoc_child(pid_t pid, t_data *data, int index)
{
	int	status;

	close(data->here[index].pipefd[1]);
	data->here[index].pipefd[1] = -1;
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) || WEXITSTATUS(status) != 0)
	{
		close(data->here[index].pipefd[0]);
		data->here[index].pipefd[0] = -1;
		return (0);
	}
	return (1);
}

int	process_single_here_doc(t_data *data, char *delim, int index)
{
	pid_t	pid;

	if (!setup_heredoc_pipe(data, index))
		return (0);
	if (!duplicate_delimiter(data, delim, index))
		return (0);
	pid = create_heredoc_child(data, delim, index);
	if (pid == -1)
		return (0);
	if (pid > 0)
		return (wait_heredoc_child(pid, data, index));
	return (1);
}
