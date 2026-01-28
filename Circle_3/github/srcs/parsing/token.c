/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:42:22 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/05/29 23:24:18 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	fill_cmd(t_data *data, t_cmd *cmd, t_token *lexer)
{
	t_redirs	*n_redir;

	while (lexer)
	{
		if (is_redirection_token(lexer->type))
		{
			n_redir = new_redir(lexer->type, lexer->next->value);
			add_redir(&cmd->redirs, n_redir);
			lexer = lexer->next->next;
		}
		else if (lexer->type == WORD)
		{
			append_arg(cmd, lexer->value, data);
			lexer = lexer->next;
		}
		else if (lexer->type == PIPE)
		{
			cmd->is_pipe = 1;
			cmd->next = new_cmd_node();
			cmd = cmd->next;
			lexer = lexer->next;
		}
	}
}

void	add_redir(t_redirs **head, t_redirs *new)
{
	t_redirs	*current;

	if (!head || !new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}

t_redirs	*new_redir(t_tokens type, char *file)
{
	t_redirs	*r;

	r = mem_manager(MALLOC, sizeof(t_redirs), NULL);
	if (!r)
	{
		return (NULL);
	}
	r->type = type;
	r->file = clean_quotes(file);
	r->next = NULL;
	return (r);
}

t_cmd	*new_cmd_node(void)
{
	t_cmd	*node;

	node = mem_manager(MALLOC, sizeof(t_cmd), NULL);
	if (!node)
		return (NULL);
	node->args = NULL;
	node->redirs = NULL;
	node->is_pipe = 0;
	node->next = NULL;
	return (node);
}

void	append_arg(t_cmd *cmd, char *value, t_data *data)
{
	char	**new_args;
	char	*value_copy;
	char	*expanded_value;
	char	*final_arg;

	value_copy = ft_strdup_mem(value);
	if (!value_copy)
		return ;
	expanded_value = do_expand(value_copy, data);
	if (value)
		value_copy = ft_strchr(value, '=');
	if (value_copy && value_copy != value)
	{
		final_arg = clean_quotes(expanded_value);
		if (!final_arg)
			final_arg = ft_strdup_mem("");
		new_args = handle_single_token(cmd, final_arg);
	}
	else
		new_args = other_tokens(value, expanded_value, cmd);
	if (cmd->args)
		mem_manager(FREE, 0, cmd->args);
	cmd->args = new_args;
}
