/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:23:53 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/03/03 18:03:26 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef    MINITALK_H
# define  MINITALK_H

# include <signal.h>
# include "../libft/libft.h"
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

# define MAX_LENGHT 1000000

/*Client.c*/
void	ack_handler(int signal);
void	send_bit(pid_t pid, int bit);
void	send_charactere(pid_t pid, char c);
void	send_message(pid_t pid, const char *message);

/*Client_utils.c*/
void	init_sigaction(struct sigaction *sa);

/*Serveur.c*/
void	init_and_malloc(char **received_message);
void	end_of_handle(char **r_m, pid_t s_pid, int *char_index, int *bit_index);
void	handle_signal(int sig, siginfo_t *info, void *context);
void	init_sigaction_serveur(struct sigaction *sa);

/*Serveur_utils.c*/
void	clean_exit(char *received_message);

#endif