/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:25:35 by dimitrendaf       #+#    #+#             */
/*   Updated: 2025/06/14 15:32:17 by dtrendaf         ###   ########.fr       */
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

int main(int argc, char **argv)
{
	char **map;
	
	ft_arguments_checker(argc);
	map = file_parsing(argv);
	strip_trailing_newlines(map);
	// printf("%s\n", map[0]);
	// for (int i = 0; map[i] != NULL; i++)
	// {
	// 	printf("%s", map[i]);
	// }
	if (map_parsing(map) == -1)
		return (-1);
	// (void)map;
	// t_data  *game = init_game(map);
	// cast_rays(game, game->player, game->ray, game->map);
	// minimap(game);
    // mlx_key_hook(game->mlx, key_callback, game);
	// mlx_loop(game->mlx);
    // free(game->ray);
    // // free(game->map->m);
    // free(game->map);
    // free(game->player);
    // free(game);
    // return(0);
}
