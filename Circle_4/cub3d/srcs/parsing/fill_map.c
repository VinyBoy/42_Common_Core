/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:44:48 by oztozdem          #+#    #+#             */
/*   Updated: 2025/07/11 12:55:06 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	get_max_line_len(char **map)
{
	int	i;
	int	max_len;
	int	current_len;

	i = 0;
	max_len = 0;
	while (map[i])
	{
		current_len = ft_strlen(map[i]);
		if (current_len > max_len)
			max_len = current_len;
		i++;
	}
	return (max_len);
}

char	*fill_line(char **map, char *line, int line_index, int target_length)
{
	char	*new_line;
	int		i;
	int		original_len;

	new_line = malloc(sizeof(char) * (target_length + 1));
	if (!new_line)
		return (NULL);
	original_len = ft_strlen(line);
	i = -1;
	while (++i < original_len)
	{
		if (line[i] == ' ')
		{
			if (v_or_x(map, line_index, i) == 'V')
				new_line[i] = 'V';
			else
				new_line[i] = 'X';
		}
		else
			new_line[i] = line[i];
	}
	while (i < target_length)
		new_line[i++] = 'X';
	new_line[target_length] = '\0';
	return (new_line);
}

char	**fill_map(char **map)
{
	char	**new_map;
	int		max_len;
	int		i;
	int		map_size;

	if (!map)
		return (NULL);
	max_len = get_max_line_len(map);
	map_size = 0;
	while (map[map_size])
		map_size++;
	new_map = ft_calloc(map_size + 1, sizeof(char *));
	if (!new_map)
		return (NULL);
	i = -1;
	while (++i < map_size)
	{
		new_map[i] = fill_line(map, map[i], i, max_len);
		if (!new_map[i])
			return (free_array(new_map), NULL);
	}
	new_map[map_size] = NULL;
	return (new_map);
}
