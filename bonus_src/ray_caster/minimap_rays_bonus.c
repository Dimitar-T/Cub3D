/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_rays_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:22:35 by jwardeng          #+#    #+#             */
/*   Updated: 2025/06/17 16:51:56 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"

// calculates delta (difference) between px and ray hit and uses dda for steps
void	mm_draw_ray(t_data *game, t_player *player, t_ray *ray)
{
	double	x_inc;
	double	y_inc;
	double	difx;
	double	dify;
	int		i;

	difx = ((ray->mm_rx * MINIMAP_SCALE) - (player->px * MINIMAP_SCALE));
	dify = ((ray->mm_ry * MINIMAP_SCALE) - (player->py * MINIMAP_SCALE));
	x_inc = difx / fmax(fabs(difx), fabs(dify));
	y_inc = dify / fmax(fabs(difx), fabs(dify));
	if (game->player->px >= 0 && (int)game->player->px < game->win_width
		&& game->player->py >= 0 && (int)game->player->py < game->win_height
		&& game->ray->mm_rx >= 0 && (int)game->ray->mm_rx < game->win_width
		&& game->ray->mm_ry >= 0 && (int)game->ray->mm_ry < game->win_height)
	{
		i = 1;
		while (i <= fmax(fabs(difx), fabs(dify)))
		{
			mlx_put_pixel(game->img, (int)(game->player->px * MINIMAP_SCALE + i
					* x_inc), (int)(game->player->py * MINIMAP_SCALE + i
					* y_inc), 0x00FF00FF);
			i++;
		}
	}
}

// checks for wall_hits
void	mm_find_wall(t_ray *ray, t_map *map)
{
	int	map_x;
	int	map_y;

	while (1)
	{
		if (ray->ra >= M_PI)
			map_y = (int)((ray->mm_ry - 1) / 64);
		else
			map_y = (int)(ray->mm_ry / 64);
		if (ray->ra >= M_PI / 2 && ray->ra <= 3 * M_PI / 2)
			map_x = (int)((ray->mm_rx - 1) / 64);
		else
			map_x = (int)(ray->mm_rx / 64);
		if (map_x >= 0 && map_y >= 0 && map_x < map->mx && map_y < map->my)
		{
			if (map->m[map_y][map_x] == '1')
				break ;
		}
		else
			break ;
		ray->mm_rx += ray->rdx * 2.5;
		ray->mm_ry += ray->rdy * 2.5;
	}
}

// starts casting rays at -30° (from pa) and keep increasing up to + 30°
// step decides how many rays will be drawn
void	mm_cast_rays(t_data *game, t_player *player, t_ray *ray, t_map *map)
{
	int		x;
	double	start_angle;
	int		step;

	x = 0;
	step = 100;
	start_angle = player->pa - FOV / 2;
	while (x < game->win_width)
	{
		ray->ra = start_angle + (FOV * x / game->win_width);
		ray->mm_rx = player->px;
		ray->mm_ry = player->py;
		ray->rdx = cos(ray->ra);
		ray->rdy = sin(ray->ra);
		mm_find_wall(ray, map);
		mm_draw_ray(game, player, ray);
		x += step;
	}
}
