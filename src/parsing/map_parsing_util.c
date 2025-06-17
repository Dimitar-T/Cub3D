/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:35:35 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/06/17 18:12:02 by dtrendaf         ###   ########.fr       */
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
			(*data)->floor = ((*data)->floor * pow(10, ft_strlen(split[i]))) + value;
		if (f_or_c == 1)
			(*data)->sky_color = ((*data)->sky_color * pow(10, ft_strlen(split[i]))) + value;
		printf("f1 %d s1 %d\n", (*data)->floor, (*data)->sky_color);
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

void validate_texture_path(char *path, char *key, t_data **data)
{
	if(valid_texture_extention(path) == false)
		exit_fail("Cub3D: Error texture is not in a valid format\n");
	while (*path == ' ')
		path++;
	if (!path || ft_strlen(path) == 0)
		exit_fail("Cub3D: Empty texture path\n");
	printf("debug %s\n", path);
	get_fd(path);
	if(key[0] == 'E') //EWSN
    	(* data)->te = mlx_load_png(path);
	else if(key[0] == 'W')
		(* data)->tw = mlx_load_png(path);
	else if(key[0] == 'S')
		(* data)->ts = mlx_load_png(path);
	else if(key[0] == 'N')
    	(* data)->te = mlx_load_png(path);
    // if ((* data)->tn == NULL || (* data)->ts == NULL || (* data)->tw == NULL || (* data)->te == NULL)
    // exit_fail("init: mlx failed to load png");
}
