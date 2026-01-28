/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:42:33 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/05/27 18:55:06 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_tokens	get_token(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '<')
	{
		if (str[i + 1] == '<')
		{
			if (str[i + 2] == '<')
				return (LESS_LESS_LESS);
			return (LESS_LESS);
		}
		return (LESS);
	}
	else if (str[i] == '>')
	{
		if (str[i + 1] == '>')
			return (GREAT_GREAT);
		return (GREAT);
	}
	else if (str[i] == '|')
		return (PIPE);
	else
		return (WORD);
}

t_tokens	find_type(char *word)
{
	int	i;

	i = 0;
	if (word[i] == '|')
		return (PIPE);
	else if (word[i] == '>')
	{
		if (word[i + 1] == '>')
			return (GREAT_GREAT);
		return (GREAT);
	}
	else if (word[i] == '<')
	{
		if (word[i + 1] == '<')
		{
			if (word[i + 2] == '<')
				return (LESS_LESS_LESS);
			return (LESS_LESS);
		}
		return (LESS);
	}
	return (WORD);
}

int	len_of_args(char **args)
{
	int	n;

	n = 0;
	while (args && args[n])
		n++;
	return (n);
}

const char	*redir_type_name(t_tokens type)
{
	if (type == LESS)
		return ("<");
	if (type == LESS_LESS)
		return ("<<");
	if (type == GREAT)
		return (">");
	if (type == GREAT_GREAT)
		return (">>");
	return ("?");
}

void	return_error_double_pipe(void)
{
	ft_dprintf(2, "minishell: syntaxerror near unexpected token `||'\n");
	return ;
}
