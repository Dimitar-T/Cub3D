/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:18:12 by jwardeng          #+#    #+#             */
/*   Updated: 2025/06/19 14:31:42 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "moves.h"

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

void	change_direction(mlx_key_data_t data, t_player *player)
{
	if (data.key == MLX_KEY_RIGHT)
	{
		player->pa += 0.02;
		player->pdx = cos(player->pa);
		player->pdy = sin(player->pa);
	}
	else if (data.key == MLX_KEY_LEFT)
	{
		player->pa -= 0.02;
		player->pdx = cos(player->pa);
		player->pdy = sin(player->pa);
	}
}

static void	update_mouse(t_data **game, t_player **p)
{
	int cur_x;
	int cur_y;
	int center_x;
	double delta_x;

	center_x = (* game)->win_width / 2;
	mlx_get_mouse_pos((* game)->mlx, &cur_x, &cur_y);
	delta_x = (cur_x - center_x) * 0.0003; // sensitivity factor
	if (delta_x != 0)
	{
		(* p)->pa += delta_x;
		(* p)->pdx = cos((* p)->pa);
		(* p)->pdy = sin((* p)->pa);
		mlx_set_mouse_pos((* game)->mlx, center_x, cur_y);
	}
}

void	update_keys(void *param)
{
	t_data *game;
	t_player *p;
	
	game = (t_data *)param;
	p = game->player;
	update_mouse(&game, &p);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_player((mlx_key_data_t){.key = MLX_KEY_W}, p, game->map);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_player((mlx_key_data_t){.key = MLX_KEY_S}, p, game->map);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_player((mlx_key_data_t){.key = MLX_KEY_A}, p, game->map);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_player((mlx_key_data_t){.key = MLX_KEY_D}, p, game->map);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		change_direction((mlx_key_data_t){.key = MLX_KEY_LEFT}, p);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		change_direction((mlx_key_data_t){.key = MLX_KEY_RIGHT}, p);
	cast_rays(game, p, game->ray, game->map);
}

void	key_callback(mlx_key_data_t data, void *param)
{
	t_data		*game;

	game = (t_data *)param;

	if (data.action == MLX_PRESS)
	{
		if (data.key == MLX_KEY_ESCAPE)
			mlx_close_window(game->mlx);
	}
}
