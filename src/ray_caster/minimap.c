/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:25:20 by jwardeng          #+#    #+#             */
/*   Updated: 2025/06/16 14:18:21 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ray_caster.h"
#define MINIMAP_WIDTH 200
#define MINIMAP_HEIGHT 150
#define MINIMAP_OFFSET_X 10
#define MINIMAP_OFFSET_Y 10
#define MINIMAP_SCALE (10.0 / 64.0)

//drawing rays in 2D to debug
void	mm_draw_line(t_data *game, t_player *player, t_ray *ray)
{
	uint32_t	color;
	double		x_inc;
	double		y_inc;
	double		difx;
	double		dify;
	int			i;

	color = 0x00FF00FF;
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
			mlx_put_pixel(game->img, (int)(game->player->px * MINIMAP_SCALE + i * x_inc)/*  / 10 */,
				(int)(game->player->py * MINIMAP_SCALE + i * y_inc) /* / 10 */, color);
			i++;
		}
	}
}

void	mm_draw_player(t_data *game)
{
	uint32_t	color;

	color = 0xFF0000FF;
	if (game->player->px >= 0 && (int)game->player->px < game->win_width
		&& game->player->py >= 0 && (int)game->player->py < game->win_height)
	{
		mlx_put_pixel(game->img, (int)(game->player->px * (10.0 / 64.0)),
			(int)(game->player->py * (10.0 / 64.0)), color);
			mlx_put_pixel(game->img, (int)((game->player->px +1) * (10.0 / 64.0)),
			(int)(game->player->py * (10.0 / 64.0)), color);
		mlx_put_pixel(game->img, (int)((game->player->px -1) * (10.0 / 64.0)),
			(int)(game->player->py * (10.0 / 64.0)), color);
		mlx_put_pixel(game->img, (int)(game->player->px * (10.0 / 64.0)),
			(int)((game->player->py + 1) * (10.0 / 64.0)), color);
		mlx_put_pixel(game->img, (int)(game->player->px * (10.0 / 64.0)),
			(int)((game->player->py -1) * (10.0 / 64.0)), color);
	}
}

t_ray_dir	mm_ray_direction(t_ray *ray, int dir)
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

void	mm_draw_rays(t_ray *ray, t_map *map)
{
	int	map_x;
	int	map_y;

	while (1)
	{
		if (mm_ray_direction(ray, 1) == UP)
			map_y = (int)((ray->mm_ry - 1) / 64);
		else
			map_y = (int)(ray->mm_ry / 64);
		if (mm_ray_direction(ray, 0) == LEFT)
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

void	mm_rays(t_data *game, t_player *player, t_ray *ray, t_map *map)
{
	int		x;
	double	FOV;
	double	start_angle;
	int step;

	x = 0;
	step = 100;
	FOV = M_PI / 4;
	start_angle = player->pa - FOV / 2;
	while (x < game->win_width)
	{
		ray->ra = start_angle + (FOV * x / game->win_width);
		ray->mm_rx = player->px;
		ray->mm_ry = player->py;
		ray->rdx = cos(ray->ra);
		ray->rdy = sin(ray->ra);
		mm_draw_rays(ray, map);
		mm_draw_line(game, player, ray);
		x += step;
	}
}

void mm_floor_wall(mlx_image_t *img, char **map)
{
	int y;
    int x;
	uint32_t wall_color;
	uint32_t floor_color;

	wall_color = 0x404040FF;
	floor_color = 0x000000FF;
    y = 0;
    while (map[(int)floor(y / 10)])
	{
		x = 0;
        while (map[(int)floor(y / 10)][(int)floor(x / 10)] != '\0')
		{
			if (map[(int)floor(y / 10)][(int)floor(x / 10)] == '1')
			mlx_put_pixel(img, x, y, wall_color);
			else
            mlx_put_pixel(img, x, y, floor_color);
            x++;
		}
        y++;
	}
}

void minimap(t_data *game)
{
	mm_floor_wall(game->img, game->map->m);
    mm_draw_player(game);
    mm_rays(game, game->player, game->ray, game->map);
}
