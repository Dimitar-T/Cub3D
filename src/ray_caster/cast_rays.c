/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:16:43 by jwardeng          #+#    #+#             */
/*   Updated: 2025/06/19 13:15:10 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"

int	draw_walls(t_data *game, int start, int wallheight, int y)
{
	int				tex_x;
	int				tex_y;
	int				color;
	mlx_texture_t	*tex;

	tex = choose_tex(game);
	tex_x = get_tx(game, game->ray, tex);
	tex_y = get_ty(y, start, wallheight, tex);
	color = get_texture_color(tex, tex_x, tex_y);
	return (color);
}

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
		mlx_put_pixel(game->img, x, y, draw_walls(game, start, wallheight, y));
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

void	calc_hit(t_ray *ray, t_data *game, int step_x, int step_y)
{
	if (ray->vert == 1)
	{
		ray->walld = (ray->mx - ray->rx / game->tile + (1 - step_x) / 2)
			/ ray->rdx;
		ray->rx = game->player->px + ray->walld * ray->rdx * game->tile;
		ray->ry = game->player->py + ray->walld * ray->rdy * game->tile;
	}
	else
	{
		ray->walld = (ray->my - ray->ry / game->tile + (1 - step_y) / 2)
			/ ray->rdy;
		ray->rx = game->player->px + ray->walld * ray->rdx * game->tile;
		ray->ry = game->player->py + ray->walld * ray->rdy * game->tile;
	}
}

void	perform_dda(t_ray *ray, int step_x, int step_y, t_map *map)
{
	while (1)
	{
		if (ray->side_dx < ray->side_dy)
		{
			ray->side_dx += ray->delta_dx;
			ray->mx += step_x;
			ray->vert = 1;
		}
		else
		{
			ray->side_dy += ray->delta_dy;
			ray->my += step_y;
			ray->vert = 0;
		}
		if (ray->mx < 0 || ray->my < 0 || ray->mx >= map->mx
			|| ray->my >= map->my)
			break ;
		if (map->m[ray->my][ray->mx] == '1')
			break ;
	}
}

// setting delta distances (distance ray need to travel for each grid cell)
// to infinite if direction=0 else setting it
// side_distance = actual distance until next grid
void	calc_distances(t_data *game, t_ray *ray)
{
	if (ray->rdx == 0)
		ray->delta_dx = 1e30;
	else
		ray->delta_dx = fabs(1 / ray->rdx);
	if (ray->rdy == 0)
		ray->delta_dy = 1e30;
	else
		ray->delta_dy = fabs(1 / ray->rdy);
	if (ray->rdx < 0)
		ray->side_dx = (ray->rx / game->tile - ray->mx) * ray->delta_dx;
	else
		ray->side_dx = (ray->mx + 1.0 - ray->rx / game->tile) * ray->delta_dx;
	if (ray->rdy < 0)
		ray->side_dy = (ray->ry / game->tile - ray->my) * ray->delta_dy;
	else
		ray->side_dy = (ray->my + 1.0 - ray->ry / game->tile) * ray->delta_dy;
}

void	draw_rays(t_data *game, t_ray *ray, t_map *map)
{
	int	step_x;
	int	step_y;

	if (ray->rdx < 0)
		step_x = -1;
	else
		step_x = 1;
	if (ray->rdy < 0)
		step_y = -1;
	else
		step_y = 1;
	ray->mx = (int)(ray->rx / game->tile);
	ray->my = (int)(ray->ry / game->tile);
	calc_distances(game, ray);
	perform_dda(ray, step_x, step_y, map);
	calc_hit(ray, game, step_x, step_y);
}

// FOV is set to 60° so we start casting rays at
// -30° (from pa) and keep increasing up to + 30°
void	cast_rays(t_data *game, t_player *player, t_ray *ray, t_map *map)
{
	int		x;
	double	start_angle;

	x = 0;
	start_angle = player->pa - FOV / 2;
	while (x < WIN_WIDTH)
	{
		ray->ra = start_angle + (FOV * x / WIN_WIDTH);
		ray->rx = player->px;
		ray->ry = player->py;
		ray->rdx = cos(ray->ra);
		ray->rdy = sin(ray->ra);
		draw_rays(game, ray, map);
		calc_walls(x, game, ray, player);
		x++;
	}
	minimap(game);
}
