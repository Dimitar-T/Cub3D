/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycallback_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 11:14:50 by jwardeng          #+#    #+#             */
/*   Updated: 2025/06/22 11:37:25 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "moves.h"

static void	update_mouse(t_data **game, t_player **p)
{
	int		cur_x;
	int		cur_y;
	int		center_x;
	double	delta_x;

	center_x = WIN_WIDTH / 2;
	mlx_get_mouse_pos((*game)->mlx, &cur_x, &cur_y);
	delta_x = (cur_x - center_x) * 0.0007;
	if (delta_x != 0)
	{
		(*p)->pa += delta_x;
		(*p)->pdx = cos((*p)->pa);
		(*p)->pdy = sin((*p)->pa);
		mlx_set_mouse_pos((*game)->mlx, center_x, cur_y);
	}
}

void	update_keys(void *param)
{
	t_data		*game;
	t_player	*p;

	game = (t_data *)param;
	p = game->player;
	update_mouse(&game, &p);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_player(game, (mlx_key_data_t){.key = MLX_KEY_W}, p, game->map);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_player(game, (mlx_key_data_t){.key = MLX_KEY_S}, p, game->map);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_player(game, (mlx_key_data_t){.key = MLX_KEY_A}, p, game->map);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_player(game, (mlx_key_data_t){.key = MLX_KEY_D}, p, game->map);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		change_direction((mlx_key_data_t){.key = MLX_KEY_LEFT}, p);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		change_direction((mlx_key_data_t){.key = MLX_KEY_RIGHT}, p);
	cast_rays(game, p, game->ray, game->map);
}

// void	mouse_callback(double xpos, double ypos, void *param)
// {
// 	t_data *game = (t_data *)param;
// 	t_player *p = game->player;

// 	double delta_x = xpos - game->mouse_pos;
// 	game->mouse_pos = xpos;

// 	if (delta_x != 0)
// 	{
// 		// Adjust this sensitivity as needed
// 		double sensitivity = 0.0001;
// 		p->pa += delta_x * sensitivity;
// 		p->pdx = cos(p->pa);
// 		p->pdy = sin(p->pa);
// 		cast_rays(game, p, game->ray, game->map);
// 	}
// }

void	key_callback(mlx_key_data_t data, void *param)
{
	t_data	*game;

	game = (t_data *)param;
	if (data.action == MLX_PRESS)
	{
		if (data.key == MLX_KEY_ESCAPE)
			mlx_close_window(game->mlx);
	}
}
