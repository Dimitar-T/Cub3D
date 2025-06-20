/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:27:17 by jwardeng          #+#    #+#             */
/*   Updated: 2025/06/20 17:49:23 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

void	init_pos(t_data *game, char **map, t_player *player)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E'
				|| map[y][x] == 'W')
			{
				if (map[y][x] == 'N')
					player->pa = 3 * M_PI / 2;
				else if (map[y][x] == 'S')
					player->pa = M_PI / 2;
				else if (map[y][x] == 'E')
					player->pa = 0;
				else if (map[y][x] == 'W')
					player->pa = M_PI;
				player->px = x * game->tile + (game->tile / 2);
				player->py = y * game->tile + (game->tile / 2);
			}
			x++;
		}
		y++;
	}
}

t_player	*init_player(t_data *game, t_map *map)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		exit_fail("init: allocation fail\n");
	init_pos(game, map->m, player);
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

// t_sprite *init_sprite_pos(t_assets *assets, int i, int x, int y)
// {
//     t_sprite *sprite;

//     sprite = malloc(sizeof(t_sprite));
//     sprite->id = i;
//     sprite->sx = x * 64;
//     sprite->sy = y * 64;
//     sprite->ass = assets;
//     return(sprite);
// }

// t_assets *init_assets(t_data *game)
// {
//     t_assets *assets;
//     mlx_texture_t *sp1;
//     mlx_texture_t *sp2;
//     mlx_texture_t *sp3;
//     mlx_texture_t *sp4;

//     assets = malloc(sizeof(t_assets));
//     sp1 = mlx_load_png("../../textures/sprite/turtle_walk1.png");
//     sp2 = mlx_load_png("../../textures/sprite/turtle_walk2.png");
//     sp3 = mlx_load_png("../../textures/sprite/turtle_walk3.png");
//     sp4 = mlx_load_png("../../textures/sprite/turtle_walk4.png");
//     if (!sp1 || !sp2 || !sp3 || !sp4 || !game->mlx)
//     {
//         // You could also log which one failed for easier debugging
//         printf("ey\n");
//         free(assets);
//         return (NULL);
//     }
//     assets->s1 = mlx_texture_to_image(game->mlx, sp1);
//     assets->s2 = mlx_texture_to_image(game->mlx, sp2);
//     assets->s3 = mlx_texture_to_image(game->mlx, sp3);
//     assets->s4 = mlx_texture_to_image(game->mlx, sp4);
//     return(assets);
// }

// void init_sprite(char **map, t_data *game)
// {
// 	int	x;
// 	int	y;
//     int i;
//     t_assets *assets;

// 	y = 0;
//     i = 0;
//     assets = init_assets(game);
//     printf("xx\n");
// 	while (map[y])
// 	{
// 		x = 0;
// 		while (map[y][x] != '\0')
// 		{
// 			if (map[y][x] == 'T')
//             {
// 				printf("here\n");
//                 game->sprites[i] = init_sprite_pos(assets, i, x, y);
//                 printf("no\n");
//                 i++;
//             }
// 			x++;
// 		}
// 		y++;
// }
// game->sprites[i] = NULL;
// }

int	tile_size(int x, int y)
{
	int	tile_width;
	int	tile_height;

	tile_width = WIN_WIDTH / x;
	tile_height = WIN_HEIGHT / y;
	if (tile_width < tile_height)
		return (tile_width);
	else
		return (tile_height);
}

t_data	*init_game(t_data *game)
{
	game->map = init_map(game->m);
	game->tile = tile_size(game->map->mx, game->map->my);
	printf("ts %d\n", (int)game->tile);
	game->player = init_player(game, game->map);
	game->ray = init_rays(game->player);
	game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Carto", true);
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
