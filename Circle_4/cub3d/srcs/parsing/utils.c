/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:30:14 by oztozdem          #+#    #+#             */
/*   Updated: 2025/07/14 13:33:11 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	is_texture(char *line)
{
	return (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3));
}

int	is_color(char *line)
{
	return (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2));
}

int	is_map(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	return (line[i] == '1' || line[i] == '0' || line[i] == 'N' || line[i] == 'S'
		|| line[i] == 'E' || line[i] == 'W');
}

t_assets	*init_assets(void)
{
	t_assets	*assets;

	assets = malloc(sizeof(t_assets));
	if (!assets)
		return (error("Error\nMalloc error for assets\n"), NULL);
	ft_memset(assets, 0, sizeof(t_assets));
	return (assets);
}

int	is_directory(const char *path)
{
	int		fd;
	char	buffer[1];
	ssize_t	r;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (error("Error\nCannot open file\n"), 1);
	r = read(fd, buffer, 1);
	close(fd);
	if (r == -1)
		return (error("Error\nInvalid map file type\n"), 1);
	return (0);
}
