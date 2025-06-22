/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:27:17 by jwardeng          #+#    #+#             */
/*   Updated: 2025/06/22 15:17:36 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "init.h"

t_player	*init_player(t_data *game, t_map *map)
{
	t_player	*player;
	int			y;

	y = 0;
	player = malloc(sizeof(t_player));
	if (!player)
		exit_fail("init: allocation fail\n");
	player_pos(game, map->m, player, y);
	player->pdx = cos(player->pa);
	player->pdy = sin(player->pa);
	player->speed = 4.0;
	player->yo = 0;
	player->xo = 0;
	return (player);
}

t_map	*init_map(char **m)
{
	t_map	*map;
	int		y;

	map = gc_malloc(sizeof(t_map));
	if (!map)
		exit_fail("init: allocation fail\n");
	y = 0;
	map->m = m;
	map->mx = ft_strlen(map->m[0]);
	while (map->m[y] != NULL)
		y++;
	map->my = y;
	return (map);
}

t_ray	*init_rays(t_player *player)
{
	t_ray	*ray;

	ray = gc_malloc(sizeof(t_ray));
	if (!ray)
		exit_fail("init: allocation fail\n");
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
	game->map = init_map(game->m);
	game->tile = tile_size(game->map->mx, game->map->my);
	printf("ts %d\n", (int)game->tile);
	game->player = init_player(game, game->map);
	game->ray = init_rays(game->player);
	game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Carto", true);
	game->tss = 0;
	if (game->mlx == NULL)
		exit_fail("init: allocation fail\n");
	mlx_set_window_limit(game->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_WIDTH,
		WIN_HEIGHT);
	game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (game->img == NULL)
		exit_fail("init: allocation fail\n");
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) == -1)
		exit_fail("init: mlx failure image to window\n");
	game->d = mlx_load_png("textures/door.png");
	if (!game->d)
		exit_fail("init: allocation fail\n");
	game->door = 0;
	return (game);
}
