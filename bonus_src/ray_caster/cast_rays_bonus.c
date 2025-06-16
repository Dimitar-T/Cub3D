/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:16:43 by jwardeng          #+#    #+#             */
/*   Updated: 2025/06/16 18:35:29 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"

#define MINIMAP_WIDTH 200
#define MINIMAP_HEIGHT 150
#define MINIMAP_TS 8
#define MINIMAP_OFFSET_X 10
#define MINIMAP_OFFSET_Y 10
#define MINIMAP_SCALE 0.2

int	draw_walls(t_data *game, int start, int wallheight, int y)
{
	int				tex_x;
	int				tex_y;
	int				color;
	mlx_texture_t	*tex;

	tex = choose_tex(game);
	tex_x = get_tx(game->ray, tex);
	tex_y = get_ty(y, start, wallheight, tex);
	color = get_texture_color(tex, tex_x, tex_y);
	return (color);
}

// draws ceiling to top of screen, wall to middle bottom, rest floor
void	draw_scene(int start, int end, t_data *game, int x)
{
	int	y;
	int	wallheight;

	wallheight = end - start;
	y = 0;
	// printf("s %d f %d\n", game->sky_color, game->floor);
	while (y < start)
	{
		mlx_put_pixel(game->img, x, y, game->sky_color);
		y++;
	}
	while (y <= end)
	{
		mlx_put_pixel(game->img, x, y, draw_walls(game, start, wallheight, y));
		y++;
	}
	while (y < game->win_height)
	{
		mlx_put_pixel(game->img, x, y, game->floor);
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
	start = (game->win_height - height) / 2.0;
	end = start + height;
	if ((int)start < 0)
		start = 0;
	if ((int)end >= game->win_height)
		end = game->win_height - 1;
	draw_scene((int)start, (int)end, game, x);
}

int door_distance(int map_x, int map_y, t_player *player)
{
    double distance;
	
	distance = hypot(player->px - (map_x * 64 + 32), player->py - (map_y * 64 + 32));
    if (distance <= 100)
        return(1);
	else
		return(0);
}

void	draw_rays(t_data *game, t_player *player, t_ray *ray, t_map *map)
{
	int		map_x;
	int		map_y;
	double	prev_rx;
	double	prev_ry;
	int		prev_map_x;
	int		prev_map_y;

	while (1)
	{
		prev_rx = ray->rx;
		prev_ry = ray->ry;
		ray->rx += ray->rdx * 0.1;
		ray->ry += ray->rdy * 0.1;
		map_x = (int)(ray->rx / 64);
		map_y = (int)(ray->ry / 64);
		if (map_x < 0 || map_y < 0 || map_x >= map->mx || map_y >= map->my)
			break ;
		if (map->m[map_y][map_x] == '1' || (map->m[map_y][map_x] == 'D'
				&& door_distance(map_x, map_y, player) == 0))
		{
			prev_map_x = (int)(prev_rx / 64);
			prev_map_y = (int)(prev_ry / 64);
			if (prev_map_x != map_x)
				ray->vert = 1;
			else if (prev_map_y != map_y)
				ray->vert = 0;
			if (map->m[map_y][map_x] == 'D')
			game->door = 1;
			break ;
		}
	}
}

// void	draw_rays(t_ray *ray, t_map *map)
// {
// 	int		map_x;
// 	int		map_y;
// 	double	prev_rx;
// 	double	prev_ry;
// 	int		prev_map_x;
// 	int		prev_map_y;
// 	while (1)
// 	{
// 		prev_rx = ray->rx;
// 		prev_ry = ray->ry;
// 		ray->rx += ray->rdx * 0.1;
// 		ray->ry += ray->rdy * 0.1;
// 		map_x = (int)(ray->rx / 64);
// 		map_y = (int)(ray->ry / 64);
// 		if (map_x < 0 || map_y < 0 || map_x >= map->mx || map_y >= map->my)
// 			break ;
// 		if (map->m[map_y][map_x] == '1')
// 		{
// 			prev_map_x = (int)(prev_rx / 64);
// 			prev_map_y = (int)(prev_ry / 64);
// 			if (prev_map_x != map_x)
// 				ray->vert = 1;
// 			else if (prev_map_y != map_y)
// 				ray->vert = 0;
// 			break ;
// 		}
// 	}
// }

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
		x++;
	}
	minimap(game);
}
