/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 12:26:07 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/05/30 16:05:00 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	verif_quote(char *input)
{
	char	current_quote;

	current_quote = 0;
	while (*input)
	{
		if (*input == '\'' || *input == '\"')
		{
			if (current_quote == 0)
				current_quote = *input;
			else if (current_quote == *input)
				current_quote = 0;
		}
		input++;
	}
	if (current_quote == '\'')
		return (write_error("minishell: syntax error: s_quote unclosed\n"), 1);
	else if (current_quote == '\"')
		return (write_error("minishell: syntax error: d_quote unclosed\n"), 1);
	return (0);
}

int	extract_quotes(char *new_input, char *input, int *i, int *j)
{
	char	quote_type;

	if (!input[*i] || (input[*i] != '\'' && input[*i] != '\"'))
		return (0);
	quote_type = input[*i];
	(*i)++;
	while (input[*i] && input[*i] != quote_type)
	{
		new_input[*j] = input[*i];
		(*j)++;
		(*i)++;
	}
	if (input[*i] == quote_type)
		(*i)++;
	else
		return (0);
	return (1);
}

void	process_quote_character(char *new_input, char *input, int *i, int *j)
{
	int	save_i;

	save_i = *i;
	if (!extract_quotes(new_input, input, i, j))
	{
		new_input[(*j)++] = input[save_i];
		*i = save_i;
	}
	else
		(*i)--;
}

char	*clean_quotes(char *input)
{
	int		i;
	int		j;
	char	*new_input;

	i = -1;
	j = 0;
	new_input = mem_manager(MALLOC, sizeof(char) * (ft_strlen(input) + 1),
			NULL);
	if (!new_input)
		return (NULL);
	while (input[++i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			process_quote_character(new_input, input, &i, &j);
		else
			new_input[j++] = input[i];
	}
	new_input[j] = '\0';
	mem_manager(FREE, 0, input);
	return (new_input);
}
