/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:45:13 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/05/29 14:55:44 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*ft_lexer(const char *input, int i)
{
	char	*word;
	t_token	*token_list;
	t_token	*new_token;

	token_list = NULL;
	while (input[i])
	{
		while (input[i] && ft_iswspaces(input[i]))
			i++;
		if (!input[i])
			break ;
		word = analyse_and_fill_word(input, &i);
		if (!word)
			return (NULL);
		new_token = convert_word_to_token(word);
		if (!new_token)
			return (mem_manager(FREE, 0, word), NULL);
		add_token(&token_list, new_token);
		new_token = NULL;
		word = NULL;
	}
	return (token_list);
}

char	*redir_word(const char *input, char *word, int *i, int *j)
{
	if ((input[*i] == '<' && input[*i + 1] == '<') || (input[*i] == '>'
			&& input[*i + 1] == '>'))
	{
		word[(*j)++] = input[(*i)++];
		word[(*j)++] = input[(*i)++];
	}
	else
		word[(*j)++] = input[(*i)++];
	word[*j] = '\0';
	return (word);
}

int	should_break_on_delimiter(const char *input, int pos, int quote_state)
{
	int	temp_pos;

	if (quote_state != 0)
		return (0);
	if (ft_iswspaces(input[pos]) || input[pos] == '|')
		return (1);
	temp_pos = pos;
	if (is_redirection(input, &temp_pos))
		return (1);
	return (0);
}

int	calculate_word_length(const char *input, int start_pos)
{
	int	temp_i;
	int	quote_state;
	int	word_len;

	temp_i = start_pos;
	quote_state = 0;
	word_len = 0;
	while (input[temp_i])
	{
		quote_state = update_quote_state(input[temp_i], quote_state);
		if (word_len > 0 && should_break_on_delimiter(input, temp_i,
				quote_state))
			break ;
		word_len++;
		temp_i++;
	}
	return (word_len);
}

t_token	*convert_word_to_token(char *word)
{
	t_token	*new;

	new = mem_manager(MALLOC, sizeof(t_token), NULL);
	if (!new)
		return (NULL);
	new->value = word;
	new->type = get_token(word);
	new->next = NULL;
	return (new);
}
