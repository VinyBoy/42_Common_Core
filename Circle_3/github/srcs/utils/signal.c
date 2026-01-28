/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:37:45 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/05/30 00:06:50 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* Gestion du CTRL+C */
void	handle_ctrl_c(int sig)
{
	(void)sig;
	g_signal_status = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/* Gestion des signaux */
void	init_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handle_ctrl_c;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);
}

void	sig_int_child(int sig)
{
	(void)sig;
	g_signal_status = 130;
}

void	sig_quit_child(int sig)
{
	(void)sig;
	g_signal_status = 131;
}

void	handle_ctrl_d(t_data *data, int *exit_status)
{
	if (!data->input)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		(*exit_status) = data->status;
		mem_manager(FREEALL, 0, NULL);
		exit((*exit_status));
	}
}
