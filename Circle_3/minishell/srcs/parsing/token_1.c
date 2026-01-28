/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:12:47 by oztozdem          #+#    #+#             */
/*   Updated: 2025/05/29 23:41:01 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**create_new_args_array(int original_count, int additional_count)
{
	char	**new_args;
	int		total_size;

	total_size = original_count + additional_count + 1;
	new_args = mem_manager(MALLOC, sizeof(char *) * total_size, NULL);
	return (new_args);
}

void	copy_original_args(char **dest, char **src, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		dest[i] = src[i];
		i++;
	}
}

void	copy_tokens(char **dest, char **src, int start_pos, int count)
{
	int	j;

	j = 0;
	while (j < count)
	{
		dest[start_pos + j] = src[j];
		j++;
	}
}

char	**handle_unquoted_variables(t_cmd *cmd, char *expanded_value)
{
	char	*cleaned_after_expand;
	char	**split_tokens;
	char	**new_args;

	cleaned_after_expand = clean_quotes(expanded_value);
	if (!cleaned_after_expand)
		cleaned_after_expand = ft_strdup_mem("");
	split_tokens = split_expanded_value(cleaned_after_expand);
	new_args = handle_split_tokens(cmd, split_tokens);
	mem_manager(FREE, 0, cleaned_after_expand);
	return (new_args);
}

char	**handle_normal_case(t_cmd *cmd, char *expanded_value)
{
	char	*final_arg;
	char	**new_args;

	final_arg = clean_quotes(expanded_value);
	if (!final_arg)
		final_arg = ft_strdup_mem("");
	new_args = handle_single_token(cmd, final_arg);
	return (new_args);
}
