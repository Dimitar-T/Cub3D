/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:35:35 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/06/12 19:47:30 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void rgb_range_checker(char *row, int f_or_c, t_data **data)
{
	char	**split;
	int		i;
	int		value;
	int 	j;
	
	while (*row == 'F' || *row == 'C' || *row == ' ')
		row++;
	split = ft_split(row, ',');
	if (!split || split[0] == NULL || split[1] == NULL || split[2] == NULL || split[3] != NULL)
		exit_fail("Cub3D: RGB must be 3 numbers separated by 2 commas\n");
	i = -1;
	while (split[++i])
	{
		j = -1;	
		while (split[i][++j])
			if ((ft_isdigit(split[i][j]) == 0) && split[i][j] != '\n') 
				exit_fail("Cub3D: RGB values must be digits only\n");
		value = ft_atoi(split[i]);
		if (value < 0 || value > 255)
			exit_fail("Cub3D: RGB values must be between 0 and 255\n");
		if (f_or_c == 0)
			(*data)->floor += value;
		if (f_or_c == 1)
			(*data)->sky_color += value;
	}
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

void validate_texture_path(char *path)
{
	if(valid_texture_extention(path) == false)
		exit_fail("Cub3D: Error texture is not in a valid format\n");
	while (*path == ' ')
		path++;
	if (!path || ft_strlen(path) == 0)
		exit_fail("Cub3D: Empty texture path\n");
	get_fd(path);
}
