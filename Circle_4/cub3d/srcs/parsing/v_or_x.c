/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_or_x.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 11:17:30 by oztozdem          #+#    #+#             */
/*   Updated: 2025/07/14 18:23:01 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	get_map_height(char **map)
{
	int	height;

	height = 0;
	while (map[height])
		height++;
	return (height);
}

int	is_full_whitespaces(char **map, int i, int k)
{
	while (map[i][k] && map[i][k] == ' ')
		k++;
	if (!map[i][k])
		return (1);
	return (0);
}

int	is_space_enclosed(char **map, int i, int j, char **visited)
{
	int	map_height;

	map_height = get_map_height(map);
	if (i < 0 || j < 0 || i >= map_height || j >= (int)ft_strlen(map[i]))
		return (0);
	if (visited[i][j])
		return (1);
	visited[i][j] = 1;
	if (map[i][j] == '1' || is_player_char(map[i][j]) || map[i][j] == '0')
		return (1);
	if (map[i][j] == ' ')
	{
		return (is_space_enclosed(map, i - 1, j, visited)
			&& is_space_enclosed(map, i + 1, j, visited)
			&& is_space_enclosed(map, i, j - 1, visited)
			&& is_space_enclosed(map, i, j + 1, visited));
	}
	return (1);
}

char	**create_visited_map(char **map)
{
	char	**visited;
	int		i;
	int		j;
	int		map_height;

	map_height = get_map_height(map);
	visited = malloc(sizeof(char *) * (map_height + 1));
	if (!visited)
		return (NULL);
	i = -1;
	while (map[++i])
	{
		visited[i] = malloc(sizeof(char) * (ft_strlen(map[i]) + 1));
		if (!visited[i])
			return (free_visited(visited, i), NULL);
		j = -1;
		while (++j < (int)ft_strlen(map[i]))
			visited[i][j] = 0;
		visited[i][j] = '\0';
	}
	visited[i] = NULL;
	return (visited);
}

char	v_or_x(char **map, int i, int j)
{
	char	**visited;
	int		result;
	int		map_height;

	map_height = get_map_height(map);
	if (i == 0 || j == 0 || i == map_height - 1 || j == (int)ft_strlen(map[i])
		- 1)
		return ('X');
	if (is_full_whitespaces(map, i, j))
		return ('X');
	visited = create_visited_map(map);
	if (!visited)
		return ('X');
	result = is_space_enclosed(map, i, j, visited);
	free_array(visited);
	if (result)
		return ('V');
	else
		return ('X');
}
