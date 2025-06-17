/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:16:43 by jwardeng          #+#    #+#             */
/*   Updated: 2025/06/17 16:58:40 by jwardeng         ###   ########.fr       */
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

//calculates the height of the walls depending on distance to player
//and deals with fisheye distortion due to difference in ray length
void	calc_walls(int x, t_data *game, t_ray *ray, t_player *player)
{
	double	dist;
	double	height;
	double	start;
	double	end;

	dist = hypot(ray->rx - player->px, ray->ry - player->py);
	dist *= cos(ray->ra - player->pa);
	height = (64.0 / dist) * (game->win_width / 2.0);
	start = (game->win_height - height) / 2.0;
	end = start + height;
	if ((int)start < 0)
		start = 0;
	if ((int)end >= game->win_height)
		end = game->win_height - 1;
	draw_scene((int)start, (int)end, game, x);
	game->door = 0;
}

void	draw_rays(t_data *game, t_player *player, t_ray *ray, t_map *map)
{
	int		map_x;
	int		map_y;
	double	prev_rx;
	double	prev_ry;

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
			ray->vert = ((int)(prev_rx / 64) != map_x);
			if (map->m[map_y][map_x] == 'D')
				game->door = 1;
			break ;
		}
	}
}

void	cast_rays(t_data *game, t_player *player, t_ray *ray, t_map *map)
{
	int		x;
	double	start_angle;

	x = 0;
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
