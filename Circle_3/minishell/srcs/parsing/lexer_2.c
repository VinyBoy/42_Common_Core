/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:46:04 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/05/26 13:07:26 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	find_flag(int in_quote)
{
	char	flag_quote;

	if (in_quote == 0)
		flag_quote = 0;
	if (in_quote == 1)
		flag_quote = '\'';
	else if (in_quote == 2)
		flag_quote = '\"';
	return (flag_quote);
}

int	len_word(const char *input, int *i, char flag_quote)
{
	int	len;
	int	j;

	j = *i;
	len = 0;
	if (input[*i] == '|')
		return (1);
	if (is_redirection(input, &j) && input[*i] != '|')
	{
		len = count_redir(input, &j);
		return (len);
	}
	if (flag_quote)
	{
		len = len_word_quote(input, j, flag_quote);
		return (len);
	}
	while (input[j] && !ft_iswspaces(input[j])
		&& !is_redirection(input, &j) && input[*i] != '|')
	{
		len++;
		j++;
	}
	return (len);
}

int	is_redirection(const char *input, int *i)
{
	if (input[*i] == '<' && input[*i + 1] == '<')
		return (1);
	if (input[*i] == '>' && input[*i + 1] == '>')
		return (1);
	if (input[*i] == '<' || input[*i] == '>')
		return (1);
	return (0);
}

int	count_redir(const char *input, int *i)
{
	if (input[*i] == '<' && input[*i + 1] == '<')
		return (2);
	if (input[*i] == '>' && input[*i + 1] == '>')
		return (2);
	if (input[*i] == '<' || input[*i] == '>')
		return (1);
	return (0);
}

int	len_word_quote(const char *input, int j, char flag_quote)
{
	int	len;

	len = 1;
	j++;
	while (input[j] && input[j] != flag_quote)
	{
		len++;
		j++;
	}
	len++;
	return (len);
}
