/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 10:35:35 by oztozdem          #+#    #+#             */
/*   Updated: 2025/07/17 10:29:54 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	if (array)
	{
		while (array[i])
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}

void	free_assets(t_assets *assets)
{
	if (assets)
	{
		if (assets->textures)
			free_array(assets->textures);
		if (assets->map)
			free_array(assets->map);
		if (assets->path_no)
			free(assets->path_no);
		if (assets->path_so)
			free(assets->path_so);
		if (assets->path_ea)
			free(assets->path_ea);
		if (assets->path_we)
			free(assets->path_we);
		if (assets->fd > 0)
		{
			close(assets->fd);
			assets->fd = -1;
		}
		free(assets);
	}
}

void	free_visited(char **visited, int i)
{
	if (!visited)
		return ;
	while (--i >= 0)
		free(visited[i]);
	free(visited);
}
