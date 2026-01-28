/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oztozdem <oztozdem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:16:21 by oztozdem          #+#    #+#             */
/*   Updated: 2025/07/08 17:27:58 by oztozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	print_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		printf("'%s'\n", array[i]);
}

void	print_floor(int tab[3])
{
	printf("F[0] = %d\n", tab[0]);
	printf("F[1] = %d\n", tab[1]);
	printf("F[2] = %d\n", tab[2]);
}

void	print_ceiling(int tab[3])
{
	printf("C[0] = %d\n", tab[0]);
	printf("C[1] = %d\n", tab[1]);
	printf("C[2] = %d\n", tab[2]);
}

void	print_assets(t_assets *assets)
{
	print_array(assets->textures);
	printf("\n");
	print_ceiling(assets->ceiling);
	printf("\n");
	print_floor(assets->floor);
	printf("\n");
	print_array(assets->map);
}
