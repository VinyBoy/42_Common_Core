/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 12:38:45 by oztozdem          #+#    #+#             */
/*   Updated: 2025/07/17 11:29:16 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_exit(t_exec *exec, int exit_code)
{
	if (exec)
	{
		if (exec->mlx)
		{
			free_all_textures(exec);
			if (exec->image)
				mlx_destroy_image(exec->mlx, exec->image);
			if (exec->win)
				mlx_destroy_window(exec->mlx, exec->win);
			mlx_destroy_display(exec->mlx);
			free(exec->mlx);
		}
		if (exec->assets)
			free_assets(exec->assets);
		free(exec);
	}
	exit(exit_code);
}
