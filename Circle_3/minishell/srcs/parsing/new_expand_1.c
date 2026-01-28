/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_expand_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:17:32 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/05/29 17:02:04 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*do_expand(char *input, t_data *data)
{
	int		in_quote;
	char	*new_input;
	int		j;

	data->i = -1;
	j = 0;
	in_quote = 0;
	new_input = mem_manager(MALLOC, sizeof(char) * 100000, NULL);
	if (!new_input)
		return (NULL);
	ft_memset(new_input, 0, 100000);
	while (input[++data->i])
	{
		in_quote = update_quotes(input[data->i], &in_quote);
		if (input[data->i] == '$' && in_quote != 1
			&& !ft_iswspaces(input[data->i + 1]) && input[data->i + 1] != '\0')
			j += expand_from_dollar(new_input, input, data, &j);
		else
		{
			new_input[j] = input[data->i];
			j++;
		}
	}
	new_input[j] = '\0';
	return (new_input);
}

int	update_quotes(char c, int *in_quote)
{
	if (c == '\'' && *in_quote == 0)
		*in_quote = 1;
	else if (c == '\'' && *in_quote == 1)
		*in_quote = 0;
	else if (c == '"' && *in_quote == 0)
		*in_quote = 2;
	else if (c == '"' && *in_quote == 2)
		*in_quote = 0;
	return (*in_quote);
}

int	is_valid_var_start(char c)
{
	if (c == '_' || ft_isalpha(c))
		return (1);
	return (0);
}

int	var_name_len(const char *s)
{
	int	i;

	i = 0;
	if (s[i] == '_' || ft_isalpha(s[i]))
	{
		i++;
		while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
			i++;
	}
	return (i);
}
