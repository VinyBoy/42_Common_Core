/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:51:57 by vnieto-j          #+#    #+#             */
/*   Updated: 2025/05/30 19:30:01 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_nl(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	if (str[i] && str[i] == '-')
	{
		i++;
		while (str[i] && str[i] == 'n')
			i++;
		if (i == len)
			return (1);
	}
	return (0);
}

static void	print_echo(char **strs, int i, int count, int nl)
{
	while (strs[i] && check_nl(strs[i]))
	{
		i++;
		nl = 0;
	}
	while (i < count)
	{
		printf("%s", strs[i]);
		if (i != count - 1 && strs[i][0] != '\0')
			printf(" ");
		i++;
	}
	if (nl)
		printf("\n");
}

void	ft_echo(char **strs, t_data *data)
{
	int		nl;
	int		i;
	int		count;

	i = 1;
	nl = 1;
	count = 0;
	while (strs[count])
		count++;
	print_echo(strs, i, count, nl);
	data->status = 0;
}
