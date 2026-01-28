/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 21:26:35 by oztozdem          #+#    #+#             */
/*   Updated: 2025/05/29 21:26:57 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	find_variable_end_brace(const char *value, int start)
{
	int	var_end;

	var_end = start;
	while (value[var_end] && value[var_end] != '}')
		var_end++;
	if (value[var_end] == '}')
		var_end++;
	return (var_end);
}

int	find_variable_end_normal(const char *value, int start)
{
	int	var_end;

	var_end = start;
	if (ft_isalpha(value[var_end]) || value[var_end] == '_')
	{
		while (value[var_end] && (ft_isalnum(value[var_end])
				|| value[var_end] == '_'))
			var_end++;
	}
	else if (value[var_end] == '?')
	{
		var_end++;
	}
	return (var_end);
}

int	check_double_quote_protection(const char *value, int i)
{
	int	var_end;
	int	is_protected;

	is_protected = 0;
	if (i > 0 && value[i - 1] == '"')
	{
		var_end = i + 1;
		if (value[var_end] == '{')
			var_end = find_variable_end_brace(value, var_end + 1);
		else
			var_end = find_variable_end_normal(value, var_end);
		if (value[var_end] == '"')
			is_protected = 1;
	}
	return (is_protected);
}

int	process_dollar_sign(const char *value, int i)
{
	int	is_protected;

	is_protected = check_double_quote_protection(value, i);
	if (!is_protected)
	{
		if (value[i + 1] && (ft_isalnum(value[i + 1]) || value[i + 1] == '_'
				|| value[i + 1] == '?'))
			return (1);
	}
	return (0);
}

int	token_contains_unprotected_expansion(const char *value)
{
	int	i;
	int	in_single_quote;
	int	in_double_quote;

	i = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (value[i])
	{
		if (value[i] == '\'')
			in_single_quote = !in_single_quote;
		else if (value[i] == '\"')
			in_double_quote = !in_double_quote;
		else if (value[i] == '$' && !in_single_quote)
		{
			if (process_dollar_sign(value, i))
				return (1);
		}
		i++;
	}
	return (0);
}
