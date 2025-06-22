/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 11:22:55 by jwardeng          #+#    #+#             */
/*   Updated: 2025/06/22 11:30:11 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "init.h"

int	tile_size(int x, int y)
{
	int	tile_width;
	int	tile_height;

	tile_width = WIN_WIDTH / x;
	tile_height = WIN_HEIGHT / y;
	if (tile_width < tile_height)
		return (tile_width);
	else
		return (tile_height);
}

void	player_pos(t_data *game, char **map, t_player *player, int y)
{
	int	x;

	while (map[y])
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E'
				|| map[y][x] == 'W')
			{
				if (map[y][x] == 'N')
					player->pa = 3 * M_PI / 2;
				else if (map[y][x] == 'S')
					player->pa = M_PI / 2;
				else if (map[y][x] == 'E')
					player->pa = 0;
				else if (map[y][x] == 'W')
					player->pa = M_PI;
				player->px = x * game->tile + (game->tile / 2);
				player->py = y * game->tile + (game->tile / 2);
			}
			x++;
		}
		y++;
	}
}
