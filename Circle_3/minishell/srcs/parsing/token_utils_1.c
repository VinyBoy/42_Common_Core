/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:14:08 by oztozdem          #+#    #+#             */
/*   Updated: 2025/05/29 20:16:50 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_tokens(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && ft_iswspaces(str[i]))
			i++;
		if (str[i])
		{
			count++;
			while (str[i] && !ft_iswspaces(str[i]))
				i++;
		}
	}
	return (count);
}

char	*extract_token(char *src, int start, int end)
{
	char	*token;
	int		j;

	token = mem_manager(MALLOC, sizeof(char) * (end - start + 1), NULL);
	if (!token)
		return (NULL);
	j = 0;
	while (start + j < end)
	{
		token[j] = src[start + j];
		j++;
	}
	token[j] = '\0';
	return (token);
}

int	fill_tokens(char **tokens, char *str, int count)
{
	int	i;
	int	idx;
	int	start;

	i = 0;
	idx = 0;
	while (str[i] && idx < count)
	{
		while (str[i] && ft_iswspaces(str[i]))
			i++;
		if (str[i])
		{
			start = i;
			while (str[i] && !ft_iswspaces(str[i]))
				i++;
			tokens[idx] = extract_token(str, start, i);
			if (!tokens[idx])
				return (0);
			idx++;
		}
	}
	tokens[count] = NULL;
	return (1);
}

char	**split_expanded_value(char *expanded_str)
{
	char	**tokens;
	int		count;
	int		ok;

	count = count_tokens(expanded_str);
	if (count == 0)
		return (NULL);
	tokens = mem_manager(MALLOC, sizeof(char *) * (count + 1), NULL);
	if (!tokens)
		return (NULL);
	ok = fill_tokens(tokens, expanded_str, count);
	if (!ok)
		return (NULL);
	return (tokens);
}

int	count_tokens_append(char **tokens)
{
	int	count;

	count = 0;
	while (tokens && tokens[count])
		count++;
	return (count);
}
