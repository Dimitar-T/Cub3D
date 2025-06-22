/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:50:03 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/06/22 15:57:29 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void check_for_dup(t_data **data)
{
	int i;

	i = -1;
	while (++i < 6)
	{
		printf("checklist: %d\n", (*data)->check_list[i]);
		if ((*data)->check_list[i] != 1)
			exit_fail("Cub3D: Error duplicate or missing configuration!\n", NULL);
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

    printf("Sky color:           %d (0x%06X)\n", data->sky_color, data->sky_color);
    printf("Floor color:         %d (0x%06X)\n", data->floor, data->floor);
    printf("Checklist:           ");
    for (int i = 0; i < 6; ++i)
        printf("%d ", data->check_list[i]);
    printf("\n");
    printf("=========================\n");
}
static void check_config(char *row, t_data **data)
{
	int i;
	bool is_a_key;
	char *temp;
	static char *key[] = {"C ", "F ", "EA ", "WE ", "SO ", "NO ", NULL};

	i = -1;
	is_a_key = false;
	while (key[++i])
	{
		if (ft_strncmp(row, key[i], ft_strlen(key[i])) == 0)
		{
			is_a_key = true;
			(*data)->check_list[i] += 1;
			if (i < 2)
				rgb_range_checker(row, i, data);
			else
				validate_texture_path(row + ft_strlen(key[i]), key[i], data);
			break;
		}
	}
	temp = ft_strjoin("Error: the following line isn't valid: ", row);
	gc_track(temp);
	if (is_a_key == false)
		exit_fail(temp, NULL);
}

static char **extract_map_only(char **map, int start_index)
{
	int count;
	int i;
	char **map_only;

	i = start_index -1;
	count = 0;
	while (map[++i])
		if (map[i][0] != '\0')
			count++;
	map_only = ft_calloc(count + 1, sizeof(char *));
	if (!map_only)
		exit_fail("Cub3D: Failed to allocate memory for map\n", NULL);
	gc_track(map_only);
	i = start_index -1;
	count = -1;
	while (map[++i])
	{  
		if (map[i][0] != '\0')
		{
			map_only[++count] = ft_strdup(map[i]);
			if (map_only[count] == NULL)
				exit_fail("Cub3D: Failed to allocate memory for map\n", NULL);
			gc_track(map_only[count]);
		}
	}
	return (map_only[count + 1] = NULL, map_only);
}

static char **configuration(char **map, t_data **data)
{
	int i;
	int count_non_empty_lines;

	i = -1;
	count_non_empty_lines = 0;
	while (map[++i] && count_non_empty_lines < 6)
	{
		if (map[i][0] == '\0' || map[i][0] == ' ')
			continue;
		count_non_empty_lines++;
		check_config(map[i], data);
	}
	print_data(*data);
	if ((* data)->tn == NULL || (* data)->ts == NULL || (* data)->tw == NULL || (* data)->te == NULL)
   		exit_fail("init: mlx failed to load png", *data);
	check_for_dup(data);
	return (extract_map_only(map, i));
}

/// check that the files that u open are not folders, and do flood fill algorithm for checking if the map is valid
/// thanks Emil <3
static void check_for_valid_chars(char **map)
{
	int player;
	int i;
	int y;

	player = 0;
	i = -1;
	while (map[++i])
	{
		y = -1;
		while (map[i][++y])
		{
			if (!ft_strchr("01NSEWD ", map[i][y]))
				exit_fail("Cub3D: Error invalid character found in map\n", NULL);
			if (ft_strchr("NSEW", map[i][y]))
				player++;
		}
	}
	if (player != 1)
		exit_fail("Cub3D: Error the map needs to conatin exactlly one player position\n", NULL);
}

t_data *map_parsing(char **map)
{
	t_data	*data;
	int		player_x;
	int		player_y;
	char	**map_copy;
	
	data = ft_calloc(1, sizeof(t_data));
	if (data == NULL)
		exit_fail("Cub3D: Error memory allocation failed!\n", NULL);
	gc_track(data);
	
	data->m = configuration(map, &data);
	for (int i = 0; data->m[i]; i++)
	{
		printf("%s\n", data->m[i]);
	}
	check_for_valid_chars(data->m);
	find_player_position(data->m, &player_y, &player_x);
	map_copy = copy_map(data->m);
	for (int i = 0; data->m[i]; i++)
	// {
	// 	printf("%s\n", data->m[i]);
	// }
	flood_fill(map_copy, player_y, player_x);
	
	
	return (data);
}
