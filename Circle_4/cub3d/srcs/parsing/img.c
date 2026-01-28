/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:15:55 by oztozdem          #+#    #+#             */
/*   Updated: 2025/07/15 16:46:08 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	*get_texture_path(char **textures, char *id)
{
	int		i;
	char	*start;

	i = 0;
	while (textures[i])
	{
		if (!ft_strncmp(textures[i], id, 3))
		{
			start = ft_strdup(textures[i] + 3);
			if (!start)
				return (NULL);
			return (start);
		}
		i++;
	}
	return (NULL);
}

int	set_path(t_assets *assets)
{
	assets->path_no = get_texture_path(assets->textures, "NO ");
	if (!assets->path_no)
		return (error("Error\nImage path setting failed\n"), 0);
	assets->path_so = get_texture_path(assets->textures, "SO ");
	if (!assets->path_so)
		return (error("Error\nImage path setting failed\n"), 0);
	assets->path_ea = get_texture_path(assets->textures, "EA ");
	if (!assets->path_ea)
		return (error("Error\nImage path setting failed\n"), 0);
	assets->path_we = get_texture_path(assets->textures, "WE ");
	if (!assets->path_we)
		return (error("Error\nImage path setting failed\n"), 0);
	assets->img_height = 128;
	assets->img_width = 128;
	return (1);
}

void	mlx_destroy_protected(void *mlx_ptr, void *img_ptr)
{
	if (img_ptr)
		mlx_destroy_image(mlx_ptr, img_ptr);
}
