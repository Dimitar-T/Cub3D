/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:27:17 by jwardeng          #+#    #+#             */
/*   Updated: 2025/05/31 23:44:15 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"

#include <math.h>
#include <stdio.h>
#include <string.h> 

void init_pos(char **map, t_player *player)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == 'N')
            {
				player->pa = 3 * M_PI / 2;
                player->px = x * 64;
                player->py = y * 64;
            }
            else if (map[y][x] == 'S')
            {
                player->pa = M_PI / 2;
                player->px = x * 64;
                player->py = y * 64;
            }
            else if (map[y][x] == 'E')
            {
                player->pa = 0;
                player->px = x * 64;
                player->py = y * 64;
            }
            else if (map[y][x] == 'W')
            {
                player->pa = M_PI;
                player->px = x * 64;
                player->py = y * 64;
            }
			x++;
		}
		y++;
	}
}

t_player   *init_player(t_map *map)
{
    t_player    *player;

    player = malloc(sizeof(t_player));
    if (!player)
    return(NULL);
    init_pos(map->m, player);
    player->pdx = cos(player->pa);
    player->pdy = sin(player->pa);
    player->speed = 4.0;
    return(player);
}

char	**mapsi(char *path)
{
	char	*tmap;
	char	**map;
	int		fd;

	map = NULL;
	tmap = malloc(1000 * sizeof(char) + 1);
	if (!tmap)
		return (NULL);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (free(tmap), NULL);
	if (read(fd, tmap, 1000) < 0)
		return (free(tmap), NULL);
	if (close(fd) < 0)
		return (free(tmap), NULL);
	map = ft_split(tmap, '\n');
	if (!map)
		return (free(tmap), NULL);
	free(tmap);
	return (map);
}

t_map   *init_map(char *m)
{
    t_map *map;
    
    map = malloc(sizeof(t_map));
    int y = 0;
    if (!map)
    return(NULL);   
    map->m = mapsi(m);
    map->mx = ft_strlen(map->m[0]);
    while (map->m[y] != NULL)
    y++;
    map->my = y;
    return(map);
}

t_ray   *init_rays(t_player *player)
{
    t_ray *ray;

    ray = malloc(sizeof(t_ray));
    if (!ray)
    return(NULL);
    ray->rx = 0;
    ray->ry = 0;
    ray->ra = player->pa;
    ray->rdx = cos(ray->ra);
    ray->rdy = cos(ray->ra);
    return(ray);
}

t_data *init_game(char *m)
{
    t_player    *player;
    t_ray       *ray;
    t_map       *map;
    t_data *game = malloc(sizeof(t_data));
    if (!game)
    return(NULL);
    game->map = init_map(m);
    game->player = init_player(game->map);
    game->ray = init_rays(game->player);
    game->win_width = game->map->mx * 64;
    game->win_height = game->map->my * 64;
    game->mlx = mlx_init(game->win_width, game->win_height, "Carto", true);
    game->img = mlx_new_image(game->mlx, game->win_width, game->win_height);
    mlx_image_to_window(game->mlx, game->img, 0, 0);
    return(game);
}
