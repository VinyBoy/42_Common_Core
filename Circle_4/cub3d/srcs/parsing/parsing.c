/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:28:08 by oztozdem          #+#    #+#             */
/*   Updated: 2025/07/23 14:33:09 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	copy_with_single_spaces(char *line, char *c_line, int *i, int *j)
{
	while (line[*i])
	{
		if (line[*i] != ' ')
			c_line[(*j)++] = line[*i];
		else if (line[*i] == ' ' && *j > 0 && c_line[*j - 1] != ' ')
			c_line[(*j)++] = ' ';
		(*i)++;
	}
}

char	*clean_line(char *line)
{
	char	*c_line;
	int		i;
	int		j;

	i = ft_strlen(line);
	if (i > 0 && line[i - 1] == '\n')
		line[i - 1] = '\0';
	c_line = malloc(sizeof(char) * (i + 1));
	if (!c_line)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i] && line[i] == ' ')
		i++;
	copy_with_single_spaces(line, c_line, &i, &j);
	if (j > 0 && c_line[j - 1] == ' ')
		j--;
	c_line[j] = '\0';
	return (c_line);
}

char	**line_to_array(char **array, char *line, int *size)
{
	char	**new_array;
	int		i;

	new_array = malloc(sizeof(char *) * (*size + 2));
	if (!new_array)
		return (NULL);
	i = 0;
	if (array)
	{
		while (i < *size)
		{
			new_array[i] = array[i];
			i++;
		}
		free(array);
	}
	new_array[i] = ft_strdup(line);
	new_array[i + 1] = NULL;
	(*size)++;
	return (new_array);
}

int	parsing(t_assets *assets)
{
	char	**filled_map;

	if (!read_map(assets))
		return (free_assets(assets), 0);
	if (!check_all_textures_present(assets))
		return (free_assets(assets), 0);
	if (!assets->map)
		return (free_assets(assets), error("Error\nNo map found\n"), 0);
	if (!check_map(assets->map))
		return (free_assets(assets), 0);
	if (!check_borders(assets->map))
		return (free_assets(assets), 0);
	filled_map = fill_map(assets->map);
	if (!filled_map)
		return (free_assets(assets), 0);
	free_array(assets->map);
	assets->map = filled_map;
	if (!check_closed(assets->map))
		return (free_assets(assets), 0);
	if (!check_textures(assets->textures))
		return (free_assets(assets), 0);
	return (1);
}

t_assets	*parse_map(char **argv)
{
	t_assets	*assets;

	assets = init_assets();
	if (!assets)
		return (error("Error\nAssets init failed\n"), NULL);
	if (is_directory(argv[1]))
		return (free_assets(assets), NULL);
	if (ft_strrchr(argv[1], '/'))
		if (ft_strlen(ft_strrchr(argv[1], '/') + 1) < 5)
			return (error("Error\nMap is wrong\n"), NULL);
	if (c_strchr(argv[1], ".cub") == 0)
		return (free_assets(assets), error("Error\nMap must be a .cub\n"), NULL);
	else
	{
		assets->fd = open(argv[1], O_RDONLY);
		if (assets->fd <= 0)
			return (error("Error\nCannot open file\n"), NULL);
		if (!parsing(assets))
			return (NULL);
	}
	assets->map_height = get_map_height(assets->map);
	assets->map_width = get_map_width(assets->map[0]);
	if (!set_path(assets))
		return (0);
	return (assets);
}
