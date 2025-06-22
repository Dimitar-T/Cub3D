/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:16:43 by jwardeng          #+#    #+#             */
/*   Updated: 2025/06/22 13:59:00 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"

// calculates the distance from player(=rx&ry) to where the ray hit
// and sets rx and ry to hit_pos
void	calc_hit(t_ray *ray, t_data *game, int step_x, int step_y)
{
	if (ray->vert == 1)
	{
		ray->walld = (ray->mx - ray->rx / game->tile + (1 - step_x) / 2)
			/ ray->rdx;
		ray->rx = ray->rx + ray->walld * ray->rdx * game->tile;
		ray->ry = ray->ry + ray->walld * ray->rdy * game->tile;
	}
	else
	{
		ray->walld = (ray->my - ray->ry / game->tile + (1 - step_y) / 2)
			/ ray->rdy;
		ray->rx = ray->rx + ray->walld * ray->rdx * game->tile;
		ray->ry = ray->ry + ray->walld * ray->rdy * game->tile;
	}
}

// checks if x or y distance is closer, increases the closer one by 1
// until it finds a hit
void	perform_dda(t_ray *ray, int step_x, int step_y, t_data *game)
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
		if (ray->mx < 0 || ray->my < 0 || ray->mx >= game->map->mx
			|| ray->my >= game->map->my)
			break ;
		// if (game->map->m[ray->my][ray->mx] == '1')
		// 	break ;
		if (game->map->m[ray->my][ray->mx] == '1' || (game->map->m[ray->my][ray->mx] == 'D'
			&& door_distance(ray->mx, ray->my, game->player, game) == 0))
	{
		if (game->map->m[ray->my][ray->mx] == 'D')
			game->door = 1;
		break ;
	}
	}
}

// setting delta distances (distance ray need to travel for each grid cell)
// to infinite if direction = 0 (to avoid division by 0)
// else setting it to how far ray travels to cross one grid cell
// side_distance = distance from ray to next grid line
// printf("ddx %d ddy %d sdx %d sdy %d\n", (int)ray->delta_dx,
//(int)ray->delta_dy, (int)ray->side_dx, (int)ray->side_dy);
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

// setup for calculations (step size depending on direction & map_x, map_y)
void	calc_rays(t_data *game, t_ray *ray)
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
	perform_dda(ray, step_x, step_y, game);
	calc_hit(ray, game, step_x, step_y);
}

// FOV is set to 60° so we start casting rays at
// -30° (from pa) and keep increasing up to + 30°
void	cast_rays(t_data *game, t_player *player, t_ray *ray)
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
		calc_rays(game, ray);
		calc_walls(x, game, ray, player);
		x++;
	}
	minimap(game);
}
