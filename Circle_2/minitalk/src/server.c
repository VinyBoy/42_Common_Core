/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:16:17 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/03/04 16:16:15 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

volatile sig_atomic_t	g_received_ack = 0;

void	init_and_malloc(char **received_message)
{
	*received_message = (char *)malloc(MAX_LENGHT);
	if (!*received_message)
	{
		ft_printf("Bad allocation of malloc");
		exit (1);
	}
	ft_memset(*received_message, 0, MAX_LENGHT);
}

void	end_of_handle(char **r_m, pid_t s_pid, int *char_index, int *bit_index)
{
	if (*r_m)
	{
		ft_printf("%s\n", *r_m);
		free(*r_m);
		*r_m = NULL;
	}
	else
		ft_printf("Warning message is already NULL\n");
	if (kill (s_pid, SIGUSR2) == -1)
	{
		ft_printf("Error kill end_of_handle\n");
		free(*r_m);
		exit (1);
	}
	*bit_index = 0;
	*char_index = 0;
}

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static char	*r_mess = NULL;
	static int	bit_index = 0;
	static int	char_index = 0;
	pid_t		sender_pid;

	(void)*context;
	sender_pid = info->si_pid;
	if (!r_mess)
		init_and_malloc(&r_mess);
	if (sig == SIGUSR1)
		r_mess[char_index] += (1 << (7 - bit_index));
	bit_index++;
	if (bit_index == 8)
	{
		bit_index = 0;
		char_index++;
		if (r_mess[char_index - 1] == '\0')
		{
			if (ft_strncmp(r_mess, "STOP_THE_SERVER", 15) == 0)
				clean_exit(r_mess);
			end_of_handle(&r_mess, sender_pid, &char_index, &bit_index);
			init_and_malloc(&r_mess);
		}
	}
	kill(sender_pid, SIGUSR1);
}

void	init_sigaction_serveur(struct sigaction *sa)
{
	sa->sa_sigaction = handle_signal;
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = SA_SIGINFO;
}

int	main(void)
{
	struct sigaction	sa;
	int					received_bits;
	int					bit_index;

	received_bits = 0;
	bit_index = 0;
	init_sigaction_serveur(&sa);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("Serveur en attente de signaux ... PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
