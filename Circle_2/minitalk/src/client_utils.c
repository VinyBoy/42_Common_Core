/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:38:07 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/03/03 17:39:24 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	init_sigaction(struct sigaction *sa)
{
	sa->sa_handler = ack_handler;
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = 0;
}
