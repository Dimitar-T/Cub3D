/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:25:35 by dimitrendaf       #+#    #+#             */
/*   Updated: 2025/06/09 14:28:16 by dtrendaf         ###   ########.fr       */
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

int main(int argc, char **argv)
{
	char **map;
	
	ft_arguments_checker(argc);
	map = file_parsing(argv);
	// printf("%s\n", map[0]);
	for (int i = 0; map[i] != NULL; i++)
	{
		printf("%s", map[i]);
	}
	if (map_parsing(map) == -1)
		return (-1);
	(void)map;
	
    
}
