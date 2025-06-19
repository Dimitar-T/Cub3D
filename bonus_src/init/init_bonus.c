/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:27:17 by jwardeng          #+#    #+#             */
/*   Updated: 2025/06/19 14:42:31 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

#include <math.h>
#include <stdio.h>
#include <string.h> 

void init_pos(char **map, t_player *player)
{
	int	x;
	int	y;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x] != '\0')
		{
			if (map[y][x] == 'N')
            {
				player->pa = 3 * M_PI / 2;
                player->px = x * 64 + 32;
                player->py = y * 64 + 32;
            }
            else if (map[y][x] == 'S')
            {
                player->pa = M_PI / 2;
                player->px = x * 64 + 32;
                player->py = y * 64 + 32;
            }
            else if (map[y][x] == 'E')
            {
                player->pa = 0;
                player->px = x * 64 + 32;
                player->py = y * 64 + 32;
            }
            else if (map[y][x] == 'W')
            {
                player->pa = M_PI;
                player->px = x * 64 + 32;
                player->py = y * 64 + 32;
            }
		}
	}
}

t_player   *init_player(t_map *map)
{
    t_player    *player;

    player = gc_malloc(sizeof(t_player));
    if (!player)
    exit_fail("init: allocation fail\n");
    init_pos(map->m, player);
    player->pdx = cos(player->pa);
    player->pdy = sin(player->pa);
    player->speed = 1.15;
    player->yo = 0;
    player->xo = 0;
    return(player);
}

t_map   *init_map(char **m)
{
    t_map *map;
    
    map = gc_malloc(sizeof(t_map));
    int y = 0;
    if (!map)
    exit_fail("init: allocation fail\n");;   
    map->m = m;
    map->mx = ft_strlen(map->m[0]);
    while (map->m[y] != NULL)
    y++;
    map->my = y;
    return(map);
}

t_ray   *init_rays(t_player *player)
{
    t_ray *ray;

    ray = gc_malloc(sizeof(t_ray));
    if (!ray)
    exit_fail("init: allocation fail\n");
    ray->rx = 0;
    ray->ry = 0;
    ray->ra = player->pa;
    ray->rdx = cos(ray->ra);
    ray->rdy = cos(ray->ra);
    ray->vert = -1;
    ray->mm_rx = 0;
    ray->mm_ry = 0;
    return(ray);
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
//         return NULL;
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

void init_textures(t_data *game)
{
    game->tn = mlx_load_png("textures/11.png");
    game->ts = mlx_load_png("textures/22.png");
    game->te = mlx_load_png("textures/33.png");
    game->tw = mlx_load_png("textures/44.png");
    game->d = mlx_load_png("textures/door.png");
    if (game->tn == NULL || game->ts == NULL || game->tw == NULL
        || game->d == NULL || game->te == NULL)
    exit_fail("init: mlx failed to load png");
}

t_data *init_game(t_data *game)
{
    game->map = init_map(game->m);
    game->player = init_player(game->map);
    game->ray = init_rays(game->player);
    game->win_width = game->map->mx * 64;
    game->win_height = game->map->my * 64;
    game->mlx = mlx_init(game->win_width, game->win_height, "Carto", true);
    if (game->mlx == NULL)
    exit_fail("init: allocation fail\n");
    game->img = mlx_new_image(game->mlx, game->win_width, game->win_height);
    if (game->img == NULL)
    exit_fail("init: allocation fail\n");
    // init_sprite(game->map->m, game);
    init_textures(game);
    if (mlx_image_to_window(game->mlx, game->img, 0, 0) == -1)
    exit_fail("init: mlx failure image to window\n");
    return(game);
}
