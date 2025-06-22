/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:18:12 by jwardeng          #+#    #+#             */
/*   Updated: 2025/06/22 11:15:37 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "moves.h"

int	is_wall(double x, double y, t_data *game, t_map *map)
{
	double	offset;

	offset = game->tile * 0.2;
	if ((int)((y + offset) / game->tile) > map->my || (int)((y - offset)
			/ game->tile) < 0 || (int)((x + offset) / game->tile) > map->mx
		|| (int)((x - offset) / game->tile) < 0)
		return (1);
	if (map->m[(int)((y + offset) / game->tile)][(int)((x + offset)
			/ game->tile)] == '1')
		return (1);
	else if (map->m[(int)((y - offset) / game->tile)][(int)((x + offset)
			/ game->tile)] == '1')
		return (1);
	else if (map->m[(int)((y + offset) / game->tile)][(int)((x - offset)
			/ game->tile)] == '1')
		return (1);
	else if (map->m[(int)((y - offset) / game->tile)][(int)((x - offset)
			/ game->tile)] == '1')
		return (1);
	else
		return (0);
}

// same as horizontal movement, but adjustes angle to
// + a quarter circle (90°) for right and - quarter circle for left
void	move_player2(t_data *game, mlx_key_data_t data, t_player *player,
		t_map *map)
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
		if (!(is_wall((player->px + pdx * player->speed), (player->py + pdy
						* player->speed), game, map)))
		{
			player->px += pdx * player->speed;
			player->py += pdy * player->speed;
		}
	}
}

// checks if the position p is moving towards is open space
// (uses current position, adds 20 px for realistic wall-distance and moves
// speed steps on the y direction + x direction)
void	move_player(t_data *game, mlx_key_data_t data, t_player *player,
		t_map *map)
{
	if (data.key == MLX_KEY_W)
	{
		if (!is_wall((player->px + player->pdx * player->speed), (player->py
					+ player->pdy * player->speed), game, map))
		{
			player->px += player->pdx * player->speed;
			player->py += player->pdy * player->speed;
		}
	}
	else if (data.key == MLX_KEY_S)
	{
		if (!(is_wall((player->px - player->pdx * player->speed), (player->py
						- player->pdy * player->speed), game, map)))
		{
			player->px -= player->pdx * player->speed;
			player->py -= player->pdy * player->speed;
		}
	}
	else
		move_player2(game, data, player, map);
}

// changes player angle around 12°
// and changes pdx/pdy (x & y direction of the current angle) accordingly
void	change_direction(mlx_key_data_t data, t_player *player)
{
	if (data.key == MLX_KEY_RIGHT)
	{
		player->pa += 0.1;
		player->pdx = cos(player->pa);
		player->pdy = sin(player->pa);
	}
	else if (data.key == MLX_KEY_LEFT)
	{
		player->pa -= 0.1;
		player->pdx = cos(player->pa);
		player->pdy = sin(player->pa);
	}
}
