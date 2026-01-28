/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 16:08:59 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/05/30 19:07:01 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	setup_stdin_redirect(int final_in_fd)
{
	int	stdin_save;

	stdin_save = -1;
	if (final_in_fd != -1)
	{
		stdin_save = dup(STDIN_FILENO);
		if (stdin_save == -1)
		{
			perror("minishell: dup stdin failed");
			return (-1);
		}
		if (dup2(final_in_fd, STDIN_FILENO) == -1)
		{
			perror("minishell: dup2 stdin failed");
			close(stdin_save);
			return (-1);
		}
	}
	return (stdin_save);
}

int	setup_stdout_redirect(int final_out_fd)
{
	int	stdout_save;

	stdout_save = -1;
	if (final_out_fd != -1)
	{
		stdout_save = dup(STDOUT_FILENO);
		if (stdout_save == -1)
		{
			perror("minishell: dup stdout failed");
			return (-1);
		}
		if (dup2(final_out_fd, STDOUT_FILENO) == -1)
		{
			perror("minishell: dup2 stdout failed");
			close(stdout_save);
			return (-1);
		}
	}
	return (stdout_save);
}

void	handle_builtin_redir(t_exec *exec, t_data *data)
{
	int	stdin_save;
	int	stdout_save;

	stdin_save = setup_stdin_redirect(exec->redir[0]->final_in_fd);
	stdout_save = setup_stdout_redirect(exec->redir[0]->final_out_fd);
	ft_builtin(exec, data, stdin_save, stdout_save);
	if (stdin_save != -1)
	{
		if (dup2(stdin_save, STDIN_FILENO) == -1)
			perror("minishell: dup2 restore stdin failed");
		close(stdin_save);
	}
	if (stdout_save != -1)
	{
		if (dup2(stdout_save, STDOUT_FILENO) == -1)
			perror("minishell: dup2 restore stdout failed");
		close(stdout_save);
	}
}

char	**line_clean(char **line)
{
	char	**clean_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[j])
	{
		if (line[j][0])
			i++;
		j++;
	}
	clean_line = mem_manager(MALLOC, sizeof(char *) * (i + 1), NULL);
	if (!clean_line)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i][0])
			clean_line[j++] = ft_strdup_mem(line[i]);
		i++;
	}
	clean_line[j] = NULL;
	return (clean_line);
}
