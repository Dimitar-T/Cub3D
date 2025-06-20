/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:25:35 by dimitrendaf       #+#    #+#             */
/*   Updated: 2025/06/20 18:46:01 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_arguments_checker(int argc)
{
	if(argc > 2 || argc < 2 )
	{
		write(2,"Cub3D: Error expected two arguments, executable and a .cub map\n",63);
		exit(EXIT_FAILURE);
	}
}
static void strip_trailing_newlines(char **map)
{
	int i = 0;

	while (map[i])
	{
		int len = ft_strlen(map[i]);
		if (len > 0 && map[i][len - 1] == '\n')
			map[i][len - 1] = '\0';
		i++;
	}
}

static void print_data(t_data *data)
{
    printf("=== t_data Debug Info ===\n");
    printf("MLX pointer:         %p\n", (void *)data->mlx);
    printf("Player pointer:      %p\n", (void *)data->player);
    printf("Ray pointer:         %p\n", (void *)data->ray);
    printf("Map pointer:         %p\n", (void *)data->map);
    printf("Map char **m:        %p\n", (void *)data->m);
    printf("Image:               %p\n", (void *)data->img);
    printf("Texture North (tn):  %p\n", (void *)data->tn);
    printf("Texture South (ts):  %p\n", (void *)data->ts);
    printf("Texture East  (te):  %p\n", (void *)data->te);
    printf("Texture West  (tw):  %p\n", (void *)data->tw);
    printf("Door Texture (d):    %p\n", (void *)data->d);
    printf("Door state:          %d\n", data->door);
    printf("Sky color:           %d (0x%06X)\n", data->sky_color, data->sky_color);
    printf("Floor color:         %d (0x%06X)\n", data->floor, data->floor);
    printf("Checklist:           ");
    for (int i = 0; i < 6; ++i)
        printf("%d ", data->check_list[i]);
    printf("\n");
    printf("=========================\n");
}

int main(int argc, char **argv)
{
	char **map;
	t_data *game;
	
	ft_arguments_checker(argc);
	map = file_parsing(argv);
	strip_trailing_newlines(map);
	// printf("%s\n", map[0]);
	// for (int i = 0; map[i] != NULL; i++)
	// {
	// 	printf("%s", map[i]);
	// }
	game = map_parsing(map);
	if (game == NULL)
		return (-1);
	init_game(game);
	print_data(game);
	printf("miao\n");
	cast_rays(game, game->player, game->ray, game->map);
	printf("miao\n");
	minimap(game);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
    mlx_key_hook(game->mlx, key_callback, game);
	mlx_loop_hook(game->mlx, update_keys, game);
	mlx_loop(game->mlx);
    gc_free_all();
    return(0);
}
