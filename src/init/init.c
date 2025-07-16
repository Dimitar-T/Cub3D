/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:27:17 by jwardeng          #+#    #+#             */
/*   Updated: 2025/07/16 14:09:24 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "init.h"

t_player	*init_player(t_data *game, t_map *map)
{
	t_player	*player;
	int			y;

	y = 0;
	player = gc_malloc(sizeof(t_player));
	if (!player)
		exit_fail("init: allocation fail\n", game);
	player_pos(game, map->m, player, y);
	player->pdx = cos(player->pa);
	player->pdy = sin(player->pa);
	player->speed = 1.0;
	player->yo = 0;
	player->xo = 0;
	return (player);
}

t_map	*init_map(char **m, t_data *game)
{
	t_map	*map;
	int		y;
	int		a;
	int		b;

	map = gc_malloc(sizeof(t_map));
	if (!map)
		exit_fail("init: allocation fail\n", game);
	y = 0;
	a = 0;
	b = 0;
	map->m = m;
	if (map->m[0])
		a = ft_strlen(map->m[0]);
	while (map->m[y] != NULL)
	{
		b = ft_strlen(map->m[y]);
		if (b > a)
			a = b;
		y++;
	}
	map->mx = a;
	map->my = y;
	return (map);
}

t_ray	*init_rays(t_player *player, t_data *game)
{
	t_ray	*ray;

	ray = gc_malloc(sizeof(t_ray));
	if (!ray)
		exit_fail("init: allocation fail\n", game);
	ray->rx = 0;
	ray->ry = 0;
	ray->ra = player->pa;
	ray->rdx = cos(ray->ra);
	ray->rdy = cos(ray->ra);
	ray->mx = 0;
	ray->my = 0;
	ray->delta_dx = 0;
	ray->delta_dy = 0;
	ray->side_dx = 0;
	ray->side_dy = 0;
	ray->walld = 0;
	ray->vert = -1;
	ray->mm_rx = 0;
	ray->mm_ry = 0;
	return (ray);
}

t_data	*init_game(t_data *game)
{
	game->map = init_map(game->m, game);
	game->tile = tile_size(game->map->mx, game->map->my);
	game->player = init_player(game, game->map);
	game->ray = init_rays(game->player, game);
	game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Carto", true);
	game->tx_mir = 0;
	if (game->mlx == NULL)
		exit_fail("init: allocation fail1\n", game);
	mlx_set_window_limit(game->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_WIDTH,
		WIN_HEIGHT);
	game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (game->img == NULL)
		exit_fail("init: allocation fail2\n", game);
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) == -1)
		exit_fail("init: mlx failure image to window\n", game);
	return (game);
}
