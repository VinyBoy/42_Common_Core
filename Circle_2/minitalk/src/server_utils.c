/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:03:04 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/03/03 18:04:03 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	clean_exit(char *received_message)
{
	ft_printf("🔴 Serveur arrêté proprement. Mémoire libérée. 🔴\n");
	free(received_message);
	exit(0);
}
