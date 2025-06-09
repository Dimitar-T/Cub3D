#include "moves.h"
// draw in 2D to debug
// void	draw_player(t_data *game)
// {
// 	uint32_t	color;

// 	color = 0xFF0000FF;
// 	if (game->player->px >= 0 && (int)game->player->px < game->win_width
// 		&& game->player->py >= 0 && (int)game->player->py < game->win_height)
// 	{
// 		mlx_put_pixel(game->img, (int)game->player->px, (int)game->player->py,
// 			color);
// 		mlx_put_pixel(game->img, ((int)game->player->px) + 1,
// 			(int)game->player->py, color);
// 		mlx_put_pixel(game->img, ((int)game->player->px) - 1,
// 			(int)game->player->py, color);
// 		mlx_put_pixel(game->img, (int)game->player->px, (int)game->player->py
// 			+ 1, color);
// 		mlx_put_pixel(game->img, (int)game->player->px, (int)game->player->py
// 			- 1, color);
// 	}
// 	draw_rays(game, game->player, game->ray, game->map);
// }

// int wall_check()
// {

// }

void	move_player2(mlx_key_data_t data, t_player *player, t_map *map)
{
	if (data.key == MLX_KEY_A)
	{
		if (map->m[(int)(player->py + sin(player->pa - M_PI / 2)
				* player->speed) / 64][(int)(player->px + cos(player->pa - M_PI
					/ 2) * player->speed) / 64] != '1')
		{
			player->px += cos(player->pa - M_PI / 2) * player->speed;
			player->py += sin(player->pa - M_PI / 2) * player->speed;
		}
	}
	else if (data.key == MLX_KEY_D)
	{
		if (map->m[(int)(player->py + sin(player->pa + M_PI / 2)
				* player->speed) / 64][(int)(player->px + cos(player->pa + M_PI
					/ 2) * player->speed) / 64] != '1')
		{
			player->px += cos(player->pa + M_PI / 2) * player->speed;
			player->py += sin(player->pa + M_PI / 2) * player->speed;
		}
	}
}

void	move_player(mlx_key_data_t data, t_player *player, t_map *map)
{
	if (data.key == MLX_KEY_W)
	{
		if (map->m[(int)(player->py + player->pdy * player->speed)
			/ 64][(int)(player->px + player->pdx * player->speed) / 64] != '1')
		{
			player->px += player->pdx * player->speed;
			player->py += player->pdy * player->speed;
		}
	}
	else if (data.key == MLX_KEY_S)
	{
		if (map->m[(int)(player->py - player->pdy * player->speed)
			/ 64][(int)(player->px - player->pdx * player->speed) / 64] != '1')
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
		player->pa += player->speed / 10;
		player->pdx = cos(player->pa);
		player->pdy = sin(player->pa);
	}
	else if (data.key == MLX_KEY_LEFT)
	{
		player->pa -= player->speed / 10;
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
