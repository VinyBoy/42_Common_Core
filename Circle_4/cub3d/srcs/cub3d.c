/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:12:08 by oztozdem          #+#    #+#             */
/*   Updated: 2025/07/23 15:17:35 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_exec		*exec;
	t_assets	*assets;

	if (argc != 2)
		return (error("Error\nUsage: ./cub3D <map.cub>\n"), 1);
	assets = parse_map(argv);
	if (!assets)
		return (1);
	exec = ft_exec(argc, argv, assets);
	if (!exec)
		return (free_assets(assets), 1);
	free_exit(exec, 0);
	return (0);
}
