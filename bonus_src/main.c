/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:25:35 by dimitrendaf       #+#    #+#             */
/*   Updated: 2025/06/22 16:57:57 by dtrendaf         ###   ########.fr       */
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



void	check_leaks(void)
{
	write(1, "Checking for leaks...\n", 22);
	system("leaks cub3D");  // use the name of your binary: cub3D or cub3D_bonus
}

int main(int argc, char **argv)
{
	char **map;
	t_data *game;
	
	atexit(check_leaks);
	ft_arguments_checker(argc);
	map = file_parsing(argv);
	strip_trailing_newlines(map);
	game = map_parsing(map);
	if (game == NULL)
		return (-1);
	init_game(game);
	cast_rays(game, game->player, game->ray);
	minimap(game);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
    mlx_key_hook(game->mlx, key_callback, game);
	mlx_loop_hook(game->mlx, update_keys, game);
	mlx_loop(game->mlx);
    exit_fail(NULL, game);
    return(0);
}
