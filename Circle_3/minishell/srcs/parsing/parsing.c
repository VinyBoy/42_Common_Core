/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:25:13 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/05/30 16:11:26 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*new_parsing(t_data *data)
{
	t_cmd	*cmd;
	t_token	*lexer;
	int		len;

	cmd = NULL;
	if (verif_quote(data->input) || is_error_syntax(data->input))
	{
		data->status = 2;
		return (NULL);
	}
	lexer = ft_lexer(data->input, 0);
	if (!lexer)
		return (NULL);
	if (!check_syntax_error_lexer(lexer))
	{
		data->status = 2;
		return (NULL);
	}
	len = nb_of_pipe(data->input);
	cmd = mem_manager(MALLOC, sizeof(t_cmd) * len, NULL);
	if (!cmd)
		return (NULL);
	init_cmd(cmd, len);
	fill_cmd(data, cmd, lexer);
	return (cmd);
}

int	nb_of_pipe(char *input)
{
	int	count;
	int	i;
	int	in_quote;

	i = -1;
	count = 1;
	in_quote = 0;
	while (input[++i])
	{
		if (input[i] == '\'' && in_quote == 0)
			in_quote = 1;
		else if (input[i] == '\'' && in_quote == 1)
			in_quote = 0;
		else if (input[i] == '\"' && in_quote == 0)
			in_quote = 2;
		else if (input[i] == '\"' && in_quote == 2)
			in_quote = 0;
		else if (input[i] == '|' && in_quote == 0)
			count++;
	}
	return (count);
}

void	init_cmd(t_cmd *cmd, int len)
{
	int	i;
	int	j;

	i = 0;
	j = i + 1;
	while (i < len)
	{
		cmd[i].args = NULL;
		cmd[i].redirs = NULL;
		cmd[i].is_pipe = 0;
		cmd[i].next = cmd->next;
		if (i + 1 < j)
			cmd[i].next = &cmd[i + 1];
		else
			cmd[i].next = NULL;
		i++;
	}
}
