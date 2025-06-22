/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:02:30 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/06/22 15:14:56 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char **copy_map(char **original)
{
	int		i;
	char	**copy;

	i = 0;
	while (original[i])
		i++;
	copy = ft_calloc(i + 1, sizeof(char *));
	if (!copy)
		exit_fail("Cub3D: Error malloc failed!\n", NULL);
	gc_track(copy);
	i = -1;
	while (original[++i])
	{
		copy[i] = ft_strdup(original[i]);
		if(!copy[i])
			exit_fail("Cub3D: Error malloc failed!\n", NULL);
		gc_track(copy[i]);
	}
	copy[i] = NULL;
	return (copy);
}

void	flood_fill(char **map, int y, int x)
{
	if (!map[y] || x < 0 || x >= (int)ft_strlen(map[y]))
		exit_fail("Cub3D: Error map is not closed (overflow)\n", NULL);
	if (map[y][x] == '1' || map[y][x] == 'F')
		return;
	if (map[y][x] == ' ')
		exit_fail("Cub3D: Map is not closed (touches space)\n", NULL);
	map[y][x] = 'F';
	flood_fill(map, y + 1, x);
	flood_fill(map, y - 1, x);
	flood_fill(map, y, x + 1);
	flood_fill(map, y, x - 1);
}

void find_player_position(char **map, int *out_y, int *out_x)
{
	int y;
	int x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (ft_strchr("NSEW", map[y][x]))
			{
				*out_y = y;
				*out_x = x;
			}
		}
	}
}
