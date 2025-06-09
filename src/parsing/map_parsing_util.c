/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:35:35 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/06/09 14:27:14 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void rgb_range_checker(char *row)
{
	char	**split;
	int		i;
	int		value;
	int 	j;
	
	while (*row == 'F' || *row == 'C' || *row == ' ')
		row++;
	printf("%s", row);
	split = ft_split(row, ',');
	if (!split || split[0] == NULL || split[1] == NULL || split[2] == NULL || split[3] != NULL)
		exit_fail("Cub3D: RGB must be 3 numbers separated by 2 commas\n");
	i = -1;
	while (split[++i])
	{
		j = -1;	
		while (split[i][++j])
		{
			printf("j is: %d\n",split[i][j]);
			if ((ft_isdigit(split[i][j]) == 0) && split[i][j] != '\n') 
				exit_fail("Cub3D: RGB values must be digits only\n");
		}
		value = ft_atoi(split[i]);
		if (value < 0 || value > 255)
			exit_fail("Cub3D: RGB values must be between 0 and 255\n");
	}		
}

