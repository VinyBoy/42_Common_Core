/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wait.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:25:36 by oztozdem          #+#    #+#             */
/*   Updated: 2025/05/29 16:13:45 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	wait_single_child(pid_t pid, int *status)
{
	if (pid <= 0)
		return (0);
	if (waitpid(pid, status, 0) == -1)
	{
		perror("minishell: waitpid");
		return (1);
	}
	return (0);
}

static int	check_signal_interrupt(int status, int *sig_type)
{
	int	sig;

	sig = 0;
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			*sig_type = SIGINT;
		else if (sig == SIGQUIT)
			*sig_type = SIGQUIT;
		return (1);
	}
	return (0);
}

static int	get_exit_status(int status)
{
	int	exit_code;

	if (WIFSIGNALED(status))
	{
		exit_code = 128 + WTERMSIG(status);
		return (exit_code);
	}
	if (WIFEXITED(status))
	{
		exit_code = WEXITSTATUS(status);
		return (exit_code);
	}
	return (0);
}

static void	print_interruption_msg(int interrupted_by_sig, int sig_type)
{
	if (interrupted_by_sig)
	{
		if (sig_type == SIGINT)
			ft_dprintf(2, "\n");
		if (sig_type == SIGQUIT)
			ft_dprintf(2, "Quit (core dumped)\n");
	}
}

int	wait_for_children(t_exec *exec)
{
	int	status;
	int	last_status;
	int	i;
	int	interrupted_by_sig;
	int	sig_type;

	last_status = 0;
	interrupted_by_sig = 0;
	sig_type = 0;
	i = -1;
	while (++i < exec->cmd_count)
	{
		if (wait_single_child(exec->pids[i], &status) == 1)
			return (1);
		if (exec->pids[i] > 0)
		{
			if (check_signal_interrupt(status, &sig_type))
				interrupted_by_sig = 1;
			if (i == exec->cmd_count - 1)
				last_status = get_exit_status(status);
		}
	}
	print_interruption_msg(interrupted_by_sig, sig_type);
	return (last_status);
}
