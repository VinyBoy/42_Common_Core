/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_expand_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:18:34 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/05/30 23:13:49 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	expand_from_dollar(char *new_input, char *input, t_data *data, int *j)
{
	if (input[data->i + 1] == '"' && input[data->i - 1] == '"')
	{
		new_input[(*j)--] = '$';
		return (2);
	}
	data->i++;
	if (input[data->i] == '"')
		return (handle_dollar_double_quote(new_input, input, data, j));
	else if (input[data->i] == '\'')
		return (handle_dollar_single_quote(new_input, input, data, j));
	else if (input[data->i] == '$')
		return (expand_pid(new_input, j));
	else if (input[data->i] == '?')
		return (expand_exit_status(new_input, input, j, data));
	else if (!ft_isalnum(input[data->i]) && input[data->i] != '_')
	{
		new_input[*j] = '$';
		data->i--;
		return (1);
	}
	else if (is_valid_var_start(input[data->i]))
		return (expand_var_env(new_input, input, data, j));
	return (0);
}

int	expand_pid(char *new_input, int *j)
{
	char	*extract_pid;
	int		len;
	int		k;

	len = 0;
	k = 0;
	extract_pid = ft_itoa_mem(getpid());
	if (!extract_pid)
		return (0);
	len = ft_strlen(extract_pid);
	while (k < len)
	{
		new_input[*j + k] = extract_pid[k];
		k++;
	}
	mem_manager(FREE, 0, extract_pid);
	return (len);
}

int	expand_exit_status(char *new_input, char *input, int *j, t_data *data)
{
	int		len;
	int		k;
	char	*extract_status;

	(void)input;
	extract_status = ft_itoa_mem(data->status);
	k = 0;
	len = ft_strlen(extract_status);
	while (k < len)
	{
		new_input[*j + k] = extract_status[k];
		k++;
	}
	mem_manager(FREE, 0, extract_status);
	return (len);
}

char	*ft_copy_var_name(const char *input, int i)
{
	int		len;
	int		j;
	char	*var_name;

	len = var_name_len(&input[i]);
	var_name = mem_manager(MALLOC, sizeof(char) * (len + 1), NULL);
	if (!var_name)
		return (NULL);
	j = 0;
	while (j < len)
	{
		var_name[j] = input[i + j];
		j++;
	}
	var_name[j] = '\0';
	return (var_name);
}

int	expand_var_env(char *new_input, char *input, t_data *data, int *j)
{
	char	*extract_var_env;
	int		var_env_len;
	char	*var_env;
	int		k;

	k = -1;
	var_env_len = 0;
	extract_var_env = ft_copy_var_name(input, data->i);
	if (!extract_var_env)
		return (0);
	var_env = ft_get_env_var(data->env, extract_var_env);
	if (!var_env)
	{
		data->i += ft_strlen(extract_var_env) - 1;
		mem_manager(FREE, 0, extract_var_env);
		return (0);
	}
	var_env_len = ft_strlen(var_env);
	while (++k < var_env_len)
		new_input[*j + k] = var_env[k];
	data->i += ft_strlen(extract_var_env) - 1;
	mem_manager(FREE, 0, extract_var_env);
	return (var_env_len);
}
