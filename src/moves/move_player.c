/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:18:12 by jwardeng          #+#    #+#             */
/*   Updated: 2025/06/16 17:18:54 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "moves.h"

// sets 20 pixel offset to wall to keep realistic distance
// if angle is negative movement on y || x is negative
void	set_offset(t_player *player, double angle_x, double angle_y)
{
	if (angle_x < 0)
		player->xo = -20;
	else
		player->xo = 20;
	if (angle_y < 0)
		player->yo = -20;
	else
		player->yo = 20;
}

// same as horizontal movement, but adjustes angle to 
// + a quarter circle (90°) for right and - quarter circle for left 
void	move_player2(mlx_key_data_t data, t_player *player, t_map *map)
{
	double	pdx;
	double	pdy;

	if (data.key == MLX_KEY_A)
	{
		pdx = cos(player->pa - M_PI / 2);
		pdy = sin(player->pa - M_PI / 2);
	}
	else if (data.key == MLX_KEY_D)
	{
		pdx = cos(player->pa + M_PI / 2);
		pdy = sin(player->pa + M_PI / 2);
	}
	if (data.key == MLX_KEY_A || data.key == MLX_KEY_D)
	{
		set_offset(player, pdx, pdy);
		if (map->m[(int)(player->py + player->yo + pdy * player->speed) / 64]
			[(int)(player->px + player->xo + pdx * player->speed) / 64] != '1')
		{
			player->px += pdx * player->speed;
			player->py += pdy * player->speed;
		}
	}
}

// checks if the position p is moving towards is open space 
// (uses current position, adds 20 px for realistic wall-distance and moves
// speed steps on the y direction + x direction)
void	move_player(mlx_key_data_t data, t_player *player, t_map *map)
{
	if (data.key == MLX_KEY_W)
	{
		set_offset(player, player->pdx, player->pdy);
		if (map->m[(int)(player->py + player->yo + player->pdy * player->speed)
			/ 64][(int)(player->px + player->xo + player->pdx * player->speed)
			/ 64] != '1')
		{
			player->px += player->pdx * player->speed;
			player->py += player->pdy * player->speed;
		}
	}
	else if (data.key == MLX_KEY_S)
	{
		set_offset(player, player->pdx, player->pdy);
		if (map->m[(int)(player->py - player->yo - player->pdy * player->speed)
			/ 64][(int)(player->px - player->xo - player->pdx * player->speed)
			/ 64] != '1')
		{
			player->px -= player->pdx * player->speed;
			player->py -= player->pdy * player->speed;
		}
	}
	else
		move_player2(data, player, map);
}

//changes player angle by 18° -> change it to fixed eg 0.1 around 6°
// and changes pdx/pdy (x & y direction of the current angle) accordingly
void	change_direction(mlx_key_data_t data, t_player *player)
{
	if (data.key == MLX_KEY_RIGHT)
	{
		player->pa += player->speed / 25;
		player->pdx = cos(player->pa);
		player->pdy = sin(player->pa);
	}
	else if (data.key == MLX_KEY_LEFT)
	{
		player->pa -= player->speed / 25;
		player->pdx = cos(player->pa);
		player->pdy = sin(player->pa);
	}
}

void	key_callback(mlx_key_data_t data, void *param)
{
	t_data		*game;
	t_player	*player;

	game = (t_data *)param;
	player = game->player;
	if (data.action == MLX_PRESS || data.action == MLX_REPEAT)
	{
		if (data.key == MLX_KEY_ESCAPE)
			mlx_close_window(game->mlx);
		else if (data.key == MLX_KEY_W || data.key == MLX_KEY_S
			|| data.key == MLX_KEY_A || data.key == MLX_KEY_D)
			move_player(data, player, game->map);
		else if (data.key == MLX_KEY_RIGHT || data.key == MLX_KEY_LEFT)
			change_direction(data, player);
		cast_rays(game, player, game->ray, game->map);
	}
}
