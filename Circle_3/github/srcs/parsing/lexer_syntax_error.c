/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:27:48 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/05/30 00:03:51 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_condition_token(int *count, t_token *cur)
{
	if (*count > 1)
		return (ft_dprintf(2, "%s `%s`\n", S_E, redir_type_name(cur->type)), 0);
	if (!cur->next)
		return (ft_dprintf(2, "%s `newline`\n", S_E), 0);
	if (cur->next->type == WORD)
		*count = 0;
	if (is_redir(cur->next->type))
		return (ft_dprintf(2, "%s `%s`\n", S_E, redir_type_name(cur->type)), 0);
	if (cur->next->type == PIPE && cur->next->next
		&& cur->next->next->type == PIPE)
		return (ft_dprintf(2, "%s `|`\n", S_E, 0), 0);
	if (cur->type == GREAT_GREAT && cur->next->type == PIPE)
		return (ft_dprintf(2, "%s `|`\n", S_E, 0), 0);
	if (cur->next->type == PIPE)
		return (ft_dprintf(2, "%s `newline`\n", S_E), 0);
	return (1);
}

int	check_redir_error(t_token *cur)
{
	int	count;

	count = 0;
	if (!cur)
		return (1);
	if (is_redir(cur->type) && cur->type != LESS_LESS && cur->type != LESS)
		return (ft_dprintf(2,
				"minishell: syntax error near unexpected token `%s`\n",
				redir_type_name(cur->type)), 0);
	else if (cur->type == LESS_LESS
		&& cur->next && cur->next->type == LESS_LESS)
		return (ft_dprintf(2, "%s `%s`\n", S_E, redir_type_name(cur->type)), 0);
	while (cur)
	{
		if (cur->type == PIPE)
			count = 0;
		if (is_redirection_token(cur->type))
		{
			count++;
			if (!check_condition_token(&count, cur))
				return (0);
		}
		cur = cur->next;
	}
	return (1);
}

int	check_pipe_error(t_token *lexer)
{
	t_token	*cur;

	cur = lexer;
	if (!cur)
		return (0);
	if (cur->type == PIPE)
	{
		if (cur->next && cur->next->type == PIPE)
			return (ft_dprintf(2,
					"minishell: syntax error near unexpected token '||'\n"), 0);
		return (ft_dprintf(2,
				"minishell: syntax error near unexpected token '|'\n"), 0);
	}
	while (cur)
	{
		if (cur->type == PIPE && cur->next == NULL)
			return (ft_dprintf(2,
					"minishell: syntax error near unexpected token '|'\n"), 0);
		if (cur->type == PIPE && cur->next && cur->next->type == PIPE)
			return (ft_dprintf(2,
					"minishell: syntax error near unexpected token '||'\n"), 0);
		cur = cur->next;
	}
	return (1);
}

int	check_syntax_error_lexer(t_token *lexer)
{
	if (!check_redir_error(lexer))
		return (0);
	if (!check_pipe_error(lexer))
		return (0);
	return (1);
}

int	is_error_syntax(const char *input)
{
	int	i;
	int	in_quote;

	i = -1;
	in_quote = 0;
	while (input[++i])
	{
		in_quote = update_quotes(input[i], &in_quote);
		if (in_quote == 0 && input[i] == '|' && input[i + 1] == '|'
			&& input[i + 2] == '|')
			return (ft_dprintf(2, "%s `|'\n", S_E), 1);
		if (in_quote == 0 && input[i] == '|' && input[i + 1] == ' ')
		{
			while ((input[++i] == ' '))
				;
			if (input[i] == '|')
				return (ft_dprintf(2, "%s '|'\n", S_E), 1);
		}
		if (in_quote == 0 && input[i] == '|' && input[i + 1] == '|')
			return (ft_dprintf(2, "%s '||'\n", S_E), 1);
		if (in_quote == 0 && input[i] == '&' && input[i + 1] == '&')
			return (ft_dprintf(2, "%s '&&'\n", S_E), 1);
	}
	return (0);
}
