/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:14:20 by oztozdem          #+#    #+#             */
/*   Updated: 2025/05/30 16:02:16 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_exec(t_exec *exec)
{
	exec->line = NULL;
	exec->path = NULL;
	exec->envp = NULL;
	exec->pids = NULL;
	exec->pipe_fds = NULL;
	exec->cmd_count = 0;
	exec->no_path = 0;
	exec->redir = NULL;
}

char	**env_to_array(t_env *env)
{
	t_env	*tmp;
	int		i;
	char	**envp;

	tmp = env;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	envp = mem_manager(MALLOC, sizeof(char *) * (i + 1), NULL);
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		envp[i] = ft_strdup_mem(env->env_var);
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	write_join_error(char *s1, char *s2, char *s3)
{
	char	*str1;
	char	*str2;

	str1 = ft_strjoin_mem(s1, s2);
	if (!str1)
		return ;
	str2 = ft_strjoin_mem(str1, s3);
	mem_manager(FREE, 0, str1);
	if (!str2)
		return ;
	write_error(str2);
	mem_manager(FREE, 0, str2);
}

void	dup_pipe_end(t_data *data, int old_fd, int new_fd, t_exec *exec)
{
	(void)data;
	(void)exec;
	if (dup2(old_fd, new_fd) == -1)
	{
		perror("minishell: dup2");
		mem_manager(FREEALL, 0, NULL);
		exit(1);
	}
	if (close(old_fd) == -1)
	{
		perror("minishell: close after dup2");
		mem_manager(FREEALL, 0, NULL);
		exit(1);
	}
}

int	count_cmds(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}
