/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:20:30 by jwardeng          #+#    #+#             */
/*   Updated: 2025/06/22 19:21:39 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"

void	refresh_image(t_data *game)
{
	if (game->img)
		mlx_delete_image(game->mlx, game->img);
	game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->img)
		exit_fail("Cub3D: Failed to create new image\n", game);
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) == -1)
		exit_fail("Cub3D: Failed to put image to window\n", game);
}

// draws ceiling to top of screen, wall to middle bottom, rest floor
void	draw_scene(int start_close, int end_close, t_data *game, int x)
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
		mlx_put_pixel(game->img, x, y, get_tex_px(game, (int)game->ray->start,
				(int)game->ray->height, y));
		y++;
	}
	while (y < WIN_HEIGHT)
	{
		mlx_put_pixel(game->img, x, y, game->floor);
		y++;
	}
	game->tss = 0;
}

// calculates height of walls depending on distance to player and tile_size
// and deals with fisheye distortion due to difference in ray length
void	calc_walls(int x, t_data *game, t_ray *ray, t_player *player)
{
	double	dist;
	double	end;
	int		start_close;
	int		end_close;

	dist = hypot(ray->rx - player->px, ray->ry - player->py);
	dist *= cos(ray->ra - player->pa);
	ray->height = (game->tile / dist) * (WIN_WIDTH / 2.0);
	ray->start = (WIN_HEIGHT - ray->height) / 2.0;
	end = ray->start + ray->height;
	start_close = (int)ray->start;
	end_close = (int)end;
	if (start_close < 0)
		start_close = 0;
	if (end_close >= WIN_HEIGHT)
		end_close = WIN_HEIGHT - 1;
	draw_scene(start_close, end_close, game, x);
}
