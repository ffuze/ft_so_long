/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:44:03 by adegl-in          #+#    #+#             */
/*   Updated: 2025/02/10 16:50:14 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "index.h"
#include <stdlib.h>

void	free_grid(t_game *game)
{
	int y;
	
	while (game->map.grid[y])
	{
		free(game->map.grid[y]);
		y++;
	}
	free(game->map.grid);
}