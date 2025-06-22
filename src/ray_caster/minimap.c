/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:25:20 by jwardeng          #+#    #+#             */
/*   Updated: 2025/06/22 17:14:49 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"

// draws player in red
void	mm_draw_player(t_data *game)
{
	int	px;
	int	py;

	px = game->player->px * (10 / game->tile);
	py = game->player->py * (10 / game->tile);
	if (game->player->px >= 0 && (int)game->player->px < WIN_WIDTH
		&& game->player->py >= 0 && (int)game->player->py < WIN_HEIGHT)
	{
		mlx_put_pixel(game->img, px, py, 0xFF0000FF);
		mlx_put_pixel(game->img, px + 1, py, 0xFF0000FF);
		mlx_put_pixel(game->img, px - 1, py, 0xFF0000FF);
		mlx_put_pixel(game->img, px, py + 1, 0xFF0000FF);
		mlx_put_pixel(game->img, px, py - 1, 0xFF0000FF);
	}
}

// draws minimap to left corner of map
// wall color set to [grey], floor color set to [black]
// tiles are scaled down to 10
void	mm_draw_map(mlx_image_t *img, char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[(int)(y / 10)])
	{
		x = 0;
		while (map[(int)(y / 10)][(int)(x / 10)] != '\0')
		{
			if (map[(int)(y / 10)][(int)(x / 10)] == '1')
				mlx_put_pixel(img, x, y, 0x404040FF);
			else
				mlx_put_pixel(img, x, y, 0x000000FF);
			x++;
		}
		y++;
	}
}

void	minimap(t_data *game)
{
	mm_draw_map(game->img, game->map->m);
	mm_draw_player(game);
	mm_cast_rays(game, game->player, game->ray, game->map);
}
