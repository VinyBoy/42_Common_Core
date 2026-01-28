/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:22:58 by oztozdem          #+#    #+#             */
/*   Updated: 2025/05/30 19:09:41 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**handle_split_tokens(t_cmd *cmd, char **split_tokens)
{
	char	**new_args;
	int		n;
	int		token_count;

	n = len_of_args(cmd->args);
	if (!split_tokens)
	{
		new_args = create_new_args_array(n, 1);
		if (!new_args)
			return (NULL);
		copy_original_args(new_args, cmd->args, n);
		new_args[n] = ft_strdup_mem("");
		new_args[n + 1] = NULL;
		return (new_args);
	}
	token_count = count_tokens_append(split_tokens);
	new_args = create_new_args_array(n, token_count);
	if (!new_args)
		return (NULL);
	copy_original_args(new_args, cmd->args, n);
	copy_tokens(new_args, split_tokens, n, token_count);
	new_args[n + token_count] = NULL;
	mem_manager(FREE, 0, split_tokens);
	return (new_args);
}

char	**handle_single_token(t_cmd *cmd, char *expanded)
{
	char	**new_args;
	int		n;

	n = len_of_args(cmd->args);
	new_args = create_new_args_array(n, 1);
	if (!new_args)
		return (NULL);
	copy_original_args(new_args, cmd->args, n);
	new_args[n] = expanded;
	new_args[n + 1] = NULL;
	return (new_args);
}

char	*process_quoted_value(char *expanded_value)
{
	char	*result;
	int		expanded_len;

	expanded_len = ft_strlen(expanded_value);
	if (expanded_len >= 2)
		result = ft_substr_mem(expanded_value, 1, expanded_len - 2);
	else
		result = ft_strdup_mem("");
	mem_manager(FREE, 0, expanded_value);
	return (result);
}

int	check_if_fully_quoted(char *value)
{
	int		value_len;
	char	quote_type;
	int		i;

	value_len = ft_strlen(value);
	if (value_len < 2)
		return (0);
	if ((value[0] != '\'' && value[0] != '\"')
		|| (value[0] != value[value_len - 1]))
		return (0);
	quote_type = value[0];
	i = 1;
	while (i < value_len - 1)
	{
		if (value[i] == quote_type)
			return (0);
		i++;
	}
	return (1);
}

char	**other_tokens(char *value, char *expanded_value, t_cmd *cmd)
{
	char	*final_arg;
	char	**new_args;

	if (check_if_fully_quoted(value))
	{
		final_arg = process_quoted_value(expanded_value);
		if (!final_arg)
			final_arg = ft_strdup_mem("");
		new_args = handle_single_token(cmd, final_arg);
	}
	else if (token_contains_unprotected_expansion(value))
		new_args = handle_unquoted_variables(cmd, expanded_value);
	else
		new_args = handle_normal_case(cmd, expanded_value);
	return (new_args);
}
