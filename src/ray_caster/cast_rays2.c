/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:20:30 by jwardeng          #+#    #+#             */
/*   Updated: 2025/06/19 13:30:28 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"

// draws ceiling to top of screen, wall to middle bottom, rest floor
void	draw_scene(int start_close, int end_close, int start, int wallheight,
		t_data *game, int x)
{
	int	y;

	y = 0;
	while (y < start_close)
	{
		mlx_put_pixel(game->img, x, y, game->sky_color);
		y++;
	}
	while (y <= end_close)
	{
		mlx_put_pixel(game->img, x, y, get_tex_px(game, start, wallheight, y));
		y++;
	}
	while (y < WIN_HEIGHT)
	{
		mlx_put_pixel(game->img, x, y, game->floor);
		y++;
	}
}

// calculates height of walls depending on distance to player and tile_size
// and deals with fisheye distortion due to difference in ray length
void	calc_walls(int x, t_data *game, t_ray *ray, t_player *player)
{
	double	dist;
	double	height;
	double	start;
	double	end;
	int		start_close;
	int		end_close;

	dist = hypot(ray->rx - player->px, ray->ry - player->py);
	dist *= cos(ray->ra - player->pa);
	height = (game->tile / dist) * (WIN_WIDTH / 2.0);
	start = (WIN_HEIGHT - height) / 2.0;
	end = start + height;
	start_close = (int)start;
	end_close = (int)end;
	if (start_close < 0)
		start_close = 0;
	if (end_close >= WIN_HEIGHT)
		end_close = WIN_HEIGHT - 1;
	draw_scene(start_close, end_close, (int)start, (int)height, game, x);
}
