/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_signals.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:20:55 by oztozdem          #+#    #+#             */
/*   Updated: 2025/05/26 16:42:49 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ctrl_d_here_doc(char *line, char *delim, t_data *data)
{
	if (!line)
	{
		ft_dprintf(2, "minishell: warning: here-document at line ");
		ft_dprintf(2, "%d delimited by end-of-file (wanted '%s')\n",
			data->count, delim);
		close_here_doc(data);
		mem_manager(FREEALL, 0, NULL);
		exit(0);
	}
}

void	sig_int_here_doc(int sig)
{
	(void)sig;
	g_signal_status = 130;
	printf("\n");
	close(0);
}
