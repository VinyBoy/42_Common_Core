/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redir_token_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:48:27 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/05/27 18:52:12 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_redir_in(t_tokens t)
{
	return (t == LESS);
}

int	is_redir_out(t_tokens t)
{
	return (t == GREAT);
}

int	is_heredoc(t_tokens t)
{
	return (t == LESS_LESS);
}

int	is_append(t_tokens t)
{
	return (t == GREAT_GREAT);
}

int	is_redirection_token(t_tokens t)
{
	return (is_redir_in(t) || is_redir_out(t) || is_heredoc(t) || is_append(t));
}
