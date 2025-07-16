/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:25:35 by dimitrendaf       #+#    #+#             */
/*   Updated: 2025/07/16 15:09:20 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_arguments_checker(int argc)
{
	if (argc > 2 || argc < 2)
	{
		write(2,
			"Cub3D: Error expected two arguments,"
			" executable and a .cub map\n",
			63);
		exit(EXIT_FAILURE);
	}
}

static void	strip_trailing_newlines(char **map)
{
	int	i;
	int	len;

	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > 0 && map[i][len - 1] == '\n')
			map[i][len - 1] = '\0';
		i++;
	}
}

int	main(int argc, char **argv)
{
	char	**map;
	t_data	*game;

	ft_arguments_checker(argc);
	map = file_parsing(argv);
	strip_trailing_newlines(map);
	game = map_parsing(map);
	if (game == NULL)
		return (-1);
	init_game(game);
	cast_rays(game, game->player, game->ray, game->map);
	mlx_key_hook(game->mlx, key_callback, game);
	mlx_loop_hook(game->mlx, update_keys, game);
	mlx_loop(game->mlx);
	exit_fail(NULL, game);
	return (0);
}
