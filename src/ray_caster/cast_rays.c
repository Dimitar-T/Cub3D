/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 23:32:12 by jwardeng          #+#    #+#             */
/*   Updated: 2025/05/31 23:33:29 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"
#include <math.h>
#include <stdio.h>
#include <string.h>


// drawing rays in 2D to debug
// void	draw_line(t_data *game)
// {
// 	uint32_t	color;
// 	t_player	*player;
// 	t_ray		*ray;
// 	double		x_inc;
// 	double		y_inc;
// 	double		steps;
// 	double		difx;
// 	double		dify;
// 	int			i;

// 	color = rand();
// 	player = game->player;
// 	ray = game->ray;
// 	difx = (ray->rx - player->px);
// 	dify = (ray->ry - player->py);
// 	// double slope = difx / dify;
// 	// if (difx > dify)
// 	// steps = difx;
// 	// else
// 	// steps = dify;
// 	steps = fmax(fabs(difx), fabs(dify));
// 	x_inc = difx / steps;
// 	y_inc = dify / steps;
// 	if (game->player->px >= 0 && (int)game->player->px < game->win_width
// 		&& game->player->py >= 0 && (int)game->player->py < game->win_height
// 		&& game->ray->rx >= 0 && (int)game->ray->rx < game->win_width
// 		&& game->ray->ry >= 0 && (int)game->ray->ry < game->win_height)
// 	{
// 		i = 1;
// 		while (i <= steps)
// 		{
// 			mlx_put_pixel(game->img, (int)(game->player->px + i * x_inc),
// 				(int)(game->player->py + i * y_inc), color);
// 			i++;
// 		}
// 	}
// }


// draws ceiling to top of screen, wall to middle bottom, rest floor
void	draw_walls(int start, int end, t_data *game, int x)
{
	int	y;

	y = 0;
	while (y < start)
	{
		mlx_put_pixel(game->img, x, y, 0x191970FF);
		y++;
	}
	while (y <= end)
	{
		mlx_put_pixel(game->img, x, y, 0xDCDCDCFF);
		y++;
	}
	while (y < game->win_height)
	{
		mlx_put_pixel(game->img, x, y, 0x404040FF);
		y++;
	}
}

// calculates the height of the walls depending on distance to player and deals with
// fisheye distortion due to difference in ray length
void	calc_walls(int x, t_data *game, t_ray *ray, t_player *player)
{
	double	dist;
	double	height;
	double	start;
	double	end;

	dist = sqrt(pow(ray->rx - player->px, 2) + pow(ray->ry - player->py, 2));
	dist *= cos(ray->ra - player->pa);
	height = (64.0 / dist) * (game->win_width / 2.0);
	start = (game->win_height - height) / 4.0;
	end = start + height;
	if ((int)start < 0)
		start = 0;
	if ((int)end >= game->win_height)
		end = game->win_height - 1;
	// printf("dist %f height %f\n", dist, height);
	draw_walls((int)start, (int)end, game, x);
}

t_ray_dir	ray_direction(t_ray *ray, int dir)
{
	if (dir == 1)
	{
		if (ray->ra >= 0 && ray->ra <= M_PI)
			return (DOWN);
		else
			return (UP);
	}
	else
	{
		if (ray->ra >= M_PI / 2 && ray->ra <= 3 * M_PI / 2)
			return (LEFT);
		else
			return (RIGHT);
	}
}

void	draw_rays(t_data *game, t_player *player, t_ray *ray, t_map *map)
{
	int	map_x;
	int	map_y;

	while (1)
	{
		if (ray_direction(ray, 1) == UP)
			map_y = (int)((ray->ry - 1) / 64);
		else
			map_y = (int)(ray->ry / 64);
		if (ray_direction(ray, 0) == LEFT)
			map_x = (int)((ray->rx - 1) / 64);
		else
			map_x = (int)(ray->rx / 64);
		if (map_x >= 0 && map_y >= 0 && map_x < map->mx && map_y < map->my)
		{
			if (map->m[map_y][map_x] == '1')
				break ;
		}
		else
			break ;
		ray->rx += ray->rdx * 0.5;
		ray->ry += ray->rdy * 0.5;
	}
}

void	cast_rays(t_data *game, t_player *player, t_ray *ray, t_map *map)
{
	int		x;
	double	FOV;
	double	start_angle;

	x = 0;
	FOV = M_PI / 3;
	start_angle = player->pa - FOV / 2;
	while (x < game->win_width)
	{
		ray->ra = start_angle + (FOV * x / game->win_width);
		ray->rx = player->px;
		ray->ry = player->py;
		ray->rdx = cos(ray->ra);
		ray->rdy = sin(ray->ra);
		draw_rays(game, player, ray, map);
		calc_walls(x, game, ray, player);
		// draw_line(game);
		x++;
	}
}

// double dist = sqrt((pow((ray->rx - player->px), 2) + pow((ray->ry
//				- player->py), 2)));
// double height = (64 / dist) * (game->win_width / 2);
// double start = (game->win_height - height) / 2;
// if (start < 0)
// start = 0;
// double end = start + height;
// printf("dist %f height %f start %f end %f\n", dist, height, start, end);
// while (start < end)
// {
// mlx_put_pixel(game->img, x, (int)start, 0x0000FF);
// start++;
// }

// void draw_rays(t_data *game, t_player *player, t_ray *ray, t_map *map)
// {
// double ray_angle = player->pa;
// int map_x = 0;
// int map_y = 0;

// ray->rx = player->px;
// ray->ry = player->py;
//     while (1)
//     {
//         if (ray_direction(ray, 1) == UP)
//             map_y = (int)((ray->ry - 1) / 64);
//         else
//             map_y = (int)(ray->ry / 64);
//         if (ray_direction(ray, 0) == LEFT)
//             map_x = (int)((ray->rx - 1) / 64);
//         else
//             map_x = (int)(ray->rx / 64);
//         printf("rx %d ry %d\n", (int)ray->rx, (int)ray->ry);
//         printf("mx %d my %d\n", map_x, map_y);
//         if (map_x >= 0 && map_y >= 0 && map_x <= map->mx && map_y <= map->my)
//         {
//         if (map->m[map_y][map_x] == '1')
//             break ;
//         }
//         else
//         return ;
//         ray->rx += cos(ray_angle) * 0.5;
//         ray->ry += sin(ray_angle) * 0.5;
//     }
//     draw_line(game);
// }
