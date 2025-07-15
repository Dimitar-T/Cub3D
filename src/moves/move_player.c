/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:18:12 by jwardeng          #+#    #+#             */
/*   Updated: 2025/07/15 17:46:36 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "moves.h"

int	is_wall(double x, double y, t_data *game, t_map *map)
{
	int	x_inc;
	int	y_inc;
	int	x_dec;
	int	y_dec;

	x_inc = (int)((x + (game->tile * 0.2)) / game->tile);
	y_inc = (int)((y + (game->tile * 0.2)) / game->tile);
	x_dec = (int)((x - (game->tile * 0.2)) / game->tile);
	y_dec = (int)((y - (game->tile * 0.2)) / game->tile);
	if (y_inc > map->my || y_dec < 0 || x_inc > map->mx || x_dec < 0)
		return (1);
	if (map->m[y_inc][x_inc] == '1')
		return (1);
	else if (map->m[y_dec][x_inc] == '1')
		return (1);
	else if (map->m[y_inc][x_dec] == '1')
		return (1);
	else if (map->m[y_dec][x_dec] == '1')
		return (1);
	else
		return (0);
}

void	move_player_ad(t_data *game, mlx_key_data_t data, t_player *p,
		t_map *map)
{
	double	new_px;
	double	new_py;

	if (data.key == MLX_KEY_A)
	{
		new_px = p->px + cos(p->pa - M_PI / 2) * p->speed;
		new_py = p->py + sin(p->pa - M_PI / 2) * p->speed;
	}
	else
	{
		new_px = p->px + cos(p->pa + M_PI / 2) * p->speed;
		new_py = p->py + sin(p->pa + M_PI / 2) * p->speed;
	}
	if (!is_wall(p->px, new_py, game, map))
		p->py = new_py;
	if (!is_wall(new_px, p->py, game, map))
		p->px = new_px;
}

void	move_player_ws(t_data *game, mlx_key_data_t data, t_player *p,
		t_map *map)
{
	double	new_px;
	double	new_py;

	if (data.key == MLX_KEY_W)
	{
		new_px = p->px + p->pdx * p->speed;
		new_py = p->py + p->pdy * p->speed;
	}
	else
	{
		new_px = p->px - p->pdx * p->speed;
		new_py = p->py - p->pdy * p->speed;
	}
	if (!is_wall(p->px, new_py, game, map))
		p->py = new_py;
	if (!is_wall(new_px, p->py, game, map))
		p->px = new_px;
}

void	change_direction(mlx_key_data_t data, t_player *player)
{
	if (data.key == MLX_KEY_RIGHT)
		player->pa += 0.1;
	else if (data.key == MLX_KEY_LEFT)
		player->pa -= 0.1;
	player->pdx = cos(player->pa);
	player->pdy = sin(player->pa);
}
