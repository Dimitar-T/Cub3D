/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_util_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:35:35 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/06/22 12:48:49 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void set_rgb(int f_or_c, t_data **data, int value, char *split)
{
	if (f_or_c == 1)
		(*data)->floor = ((*data)->floor * pow(10, ft_strlen(split))) + value;
	if (f_or_c == 0)
		(*data)->sky_color = ((*data)->sky_color * pow(10, ft_strlen(split))) + value;
}

void rgb_range_checker(char *row, int f_or_c, t_data **data)
{
	char	**split;
	int		i;
	int		value; 
	int 	j;
	
	while (*row == 'F' || *row == 'C' || *row == ' ')
		row++;
	split = ft_split(row, ',');
	gc_track(split);
	i = -1;
	while (split[++i])
	{
		gc_track(split[i]);
		j = -1;	
		while (split[i][++j])
			if ((ft_isdigit(split[i][j]) == 0) && split[i][j] != '\n') 
				exit_fail("Cub3D: RGB values must be digits only\n", *data);
		value = ft_atoi(split[i]);
		if (value < 0 || value > 255)
			exit_fail("Cub3D: RGB values must be between 0 and 255\n", *data);
		set_rgb(f_or_c, data, value, split[i]);
	}
	if (!split || split[0] == NULL || split[1] == NULL || split[2] == NULL || split[3] != NULL)
		exit_fail("Cub3D: RGB must be 3 numbers separated by 2 commas\n", *data);
}

/// @brief  add other allowed formats as long as the mlx supports them talk to joanna 
/// @param filename 
/// @return 
static int valid_texture_extention(char *filename)
{
	char *extention;

	extention = ft_strrchr(filename, '.');
	if (!extention)
		return (false);
	if (ft_strcmp(extention, ".png") == 0)
	{
		return(true);
	}
	else
		return (false);
	
}

void validate_texture_path(char *path, char *key, t_data **data)
{
	if(valid_texture_extention(path) == false)
		exit_fail("Cub3D: Error texture is not in a valid format\n", *data);
	while (*path == ' ')
		path++;
	if (!path || ft_strlen(path) == 0)
		exit_fail("Cub3D: Empty texture path\n", *data);
	// printf("debug %s\n", path);
	get_fd(path);
	if(key[0] == 'E') //EWSN
    	(*data)->te = mlx_load_png(path);
	else if(key[0] == 'W')
		(*data)->tw = mlx_load_png(path);
	else if(key[0] == 'S')
		(*data)->ts = mlx_load_png(path);
	else if(key[0] == 'N')
    	(*data)->tn = mlx_load_png(path);
  
}
