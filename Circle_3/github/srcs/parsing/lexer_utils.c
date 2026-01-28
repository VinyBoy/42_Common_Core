/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:19:40 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/05/27 18:51:09 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_lexer(t_token **head)
{
	t_token	*lst;

	lst = *head;
	while (lst)
	{
		printf(WHITE "[" CYAN "%s" PURPLE "__%s__" WHITE "]", lst->value,
			print_token(lst->type));
		lst = lst->next;
	}
	printf("\n");
}

char	*print_token(t_tokens token)
{
	if (token == WORD)
		return ("WORD");
	else if (token == PIPE)
		return ("PIPE");
	else if (token == LESS)
		return ("LESS");
	else if (token == GREAT)
		return ("GREAT");
	else if (token == LESS_LESS)
		return ("LESS_LESS");
	else if (token == GREAT_GREAT)
		return ("GREAT_GREAT");
	return ("ERROR");
}

void	add_token(t_token **head, t_token *tk)
{
	t_token	*p;

	if (!head || !tk)
		return ;
	if (!*head)
		*head = tk;
	else
	{
		p = *head;
		while (p->next)
			p = p->next;
		p->next = tk;
	}
}

int	update_quote_state(char c, int current_state)
{
	if (current_state == 0)
	{
		if (c == '\'')
			return (1);
		else if (c == '"')
			return (2);
	}
	else if (current_state == 1 && c == '\'')
		return (0);
	else if (current_state == 2 && c == '"')
		return (0);
	return (current_state);
}
