/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:50:18 by oztozdem          #+#    #+#             */
/*   Updated: 2025/05/27 18:50:36 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_special_cases(const char *input, int *i)
{
	int	temp_pos;

	if (input[*i] == '|')
		return (1);
	temp_pos = *i;
	if (is_redirection(input, &temp_pos))
		return (count_redir(input, &temp_pos));
	return (0);
}

char	*create_pipe_word(const char *input, int *i)
{
	char	*word;

	word = mem_manager(MALLOC, sizeof(char) * 2, NULL);
	if (!word)
		return (NULL);
	word[0] = input[(*i)++];
	word[1] = '\0';
	return (word);
}

char	*create_redir_word(const char *input, int *i)
{
	char	*word;
	int		j;

	j = 0;
	word = mem_manager(MALLOC, sizeof(char) * 3, NULL);
	if (!word)
		return (NULL);
	word = redir_word(input, word, i, &j);
	return (word);
}

char	*extract_normal_word(const char *input, int *i, int word_len)
{
	char	*word;
	int		j;

	j = 0;
	word = mem_manager(MALLOC, sizeof(char) * (word_len + 1), NULL);
	if (!word)
		return (NULL);
	while (j < word_len && input[*i])
	{
		word[j] = input[*i];
		j++;
		(*i)++;
	}
	word[j] = '\0';
	return (word);
}

char	*analyse_and_fill_word(const char *input, int *i)
{
	char	*word;
	int		word_len;
	int		special_len;

	special_len = handle_special_cases(input, i);
	if (special_len > 0)
	{
		if (input[*i] == '|')
			return (create_pipe_word(input, i));
		else
			return (create_redir_word(input, i));
	}
	word_len = calculate_word_length(input, *i);
	word = extract_normal_word(input, i, word_len);
	return (word);
}
