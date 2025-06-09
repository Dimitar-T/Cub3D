/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:50:03 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/06/09 14:37:13 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// static void init_config(t_config **check_list)
// {
// 	(*check_list)->ceeling_flag = 0;
// 	(*check_list)->floor_flag = 0;
// 	(*check_list)->ea_flag = 0;
// 	(*check_list)->no_flag = 0;
// 	(*check_list)->so_flag = 0;
// 	(*check_list)->we_flag = 0;
// }


/// @brief Checks a row of the .cub file for the allowed configuration flags, int y gets reused first as a flag  
/// that checks if there is a match for the row with the keys and then 
/// @param row 
static void check_config(char *row)
{
	int i;
	int y;
	char *key[] = {"C ", "F ", "EA ", "WE ", "SO ", "NO ", NULL};
	static int check_list[6] = {0,0,0,0,0,0};
	
	i = -1;
	while (key[++i])
	{
		if (ft_strncmp(row, key[i], ft_strlen(key[i])) == 0)
		{
			y = 21;
			check_list[i] += 1;
			if (i < 2)
				rgb_range_checker(row);
			else
				printf("hello blin not done yet");
		}
	}
	y = -1;
	while(++y >= 6)
	{
		if (check_list[y] > 1)
			exit_fail("duplicate configs aren't allowed");
	}
}

static char **configuration(char **map)
{
	int 		i;
	int			count_non_empty_lines;

	i = -1;
	count_non_empty_lines = 0;
	while (map[++i] && count_non_empty_lines < 6)
	{
		if(map[i][0] == '\n') // check if map can contain spaces as an empty line 
			continue;
		count_non_empty_lines++;
		check_config(map[i]);
	}
	return(NULL);
}
/// check that the files that u open are not folders, and do flood fill algorithm for checking if the map is valid
/// thanks Emil <3
int map_parsing(char **map)
{
	configuration(map);
	return(1);
}