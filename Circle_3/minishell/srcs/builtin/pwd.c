/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:02:12 by oztozdem          #+#    #+#             */
/*   Updated: 2025/05/30 00:19:37 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pwd(char **strs, t_data *data)
{
	char	buf[4096];

	if (strs[1] && strs[1][0] == '-' && strs[1][1] != '\0')
	{
		ft_dprintf(2, "minishell: pwd: %c%c: invalid option\n", strs[1][0],
			strs[1][1]);
		data->status = 2;
		return ;
	}
	if (getcwd(buf, sizeof buf) != NULL)
	{
		printf("%s\n", buf);
		data->status = 0;
	}
	else
	{
		ft_dprintf(2, "pwd: error retrieving current directory: getcwd: %s\n",
			strerror(errno));
		data->status = 1;
	}
}
