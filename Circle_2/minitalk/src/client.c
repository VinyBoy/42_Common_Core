/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:26:23 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/03/04 16:16:43 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

volatile sig_atomic_t	g_received_ack = 0;

void	ack_handler(int signal)
{
	if (signal == SIGUSR1)
		g_received_ack = 1;
	else if (signal == SIGUSR2)
		g_received_ack = 2;
}

void	send_bit(pid_t pid, int bit)
{
	int	sig;

	sig = 0;
	if (bit == 1)
		sig = SIGUSR1;
	else if (bit == 0)
		sig = SIGUSR2;
	g_received_ack = 0;
	if (kill(pid, sig) == -1)
	{
		ft_printf("Error kill send_bit\n");
		exit (1);
	}
	while (!g_received_ack)
		usleep (5000);
}

void	send_charactere(pid_t pid, char c)
{
	int	i;
	int	bit;

	i = 7;
	while (i >= 0)
	{
		bit = (c >> i) & 1;
		send_bit(pid, bit);
		i--;
	}
}

void	send_message(pid_t pid, const char *message)
{
	struct sigaction	sa;
	int					i;

	i = -1;
	init_sigaction(&sa);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (message[++i])
		send_charactere(pid, message[i]);
	send_charactere(pid, '\0');
	while (g_received_ack != 2)
		usleep(5000);
	if (g_received_ack == 2)
		ft_printf("Reception signal du server. ✅\n");
}

int	main(int argc, char **argv)
{
	pid_t		pid;
	const char	*message;

	if (argc != 3)
	{
		ft_printf("Usage: %s <PID> <MESSAGE>\n", argv[0]);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	message = argv[2];
	send_message(pid, message);
	return (0);
}
