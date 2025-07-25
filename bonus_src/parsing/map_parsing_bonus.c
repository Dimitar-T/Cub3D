/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:50:03 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/07/16 15:08:49 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	check_config(char *row, t_data **data)
{
	int			i;
	bool		is_a_key;
	char		*temp;
	static char	*key[] = {"C ", "F ", "EA ", "WE ", "SO ", "NO ", NULL};

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
			break ;
		}
	}
	temp = ft_strjoin("Error: the following line isn't valid: ", row);
	gc_track(temp);
	if (is_a_key == false)
		exit_fail(temp, *data);
}

static char	**extract_map_only(char **map, int start_index, t_data *data)
{
	int		count;
	int		i;
	char	**map_only;

	i = start_index - 1;
	count = 0;
	while (map[++i])
		if (map[i][0] != '\0')
			count++;
	gc_track(map_only = ft_calloc(count + 1, sizeof(char *)));
	if (!map_only)
		exit_fail("Cub3D: Failed to allocate memory for map\n", data);
	i = start_index - 1;
	count = -1;
	while (map[++i])
	{
		if (map[i][0] != '\0')
		{
			map_only[++count] = ft_strdup(map[i]);
			if (map_only[count] == NULL)
				exit_fail("Cub3D: Failed to allocate memory for map\n", data);
			gc_track(map_only[count]);
		}
	}
	return (map_only[count + 1] = NULL, map_only);
}

static char	**configuration(char **map, t_data **data)
{
	int	i;
	int	count_non_empty_lines;

	i = -1;
	count_non_empty_lines = 0;
	while (map[++i] && count_non_empty_lines < 6)
	{
		if (map[i][0] == '\0' || map[i][0] == ' ')
			continue ;
		count_non_empty_lines++;
		check_config(map[i], data);
	}
	if ((*data)->tn == NULL || (*data)->ts == NULL || (*data)->tw == NULL
		|| (*data)->te == NULL)
		exit_fail("init: mlx failed to load png", *data);
	check_for_dup(data);
	return (extract_map_only(map, i, *data));
}

static void	check_for_valid_chars(char **map, t_data *data)
{
	int	player;
	int	i;
	int	y;

	player = 0;
	i = -1;
	while (map[++i])
	{
		y = -1;
		while (map[i][++y])
		{
			if (!ft_strchr("01NSEWD ", map[i][y]))
				exit_fail("Cub3D: Error invalid character found in map\n",
					data);
			if (ft_strchr("NSEW", map[i][y]))
				player++;
		}
	}
	if (player != 1)
		exit_fail("Cub3D: Error the map needs to conatin exactlly one "
			"player position\n", data);
}

t_data	*map_parsing(char **map)
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
	check_for_valid_chars(data->m, data);
	find_player_position(data->m, &player_y, &player_x);
	map_copy = copy_map(data->m, data);
	flood_fill(map_copy, player_y, player_x, data);
	return (data);
}
