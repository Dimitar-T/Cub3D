/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 03:36:05 by dimitrendaf       #+#    #+#             */
/*   Updated: 2025/06/09 17:01:48 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include <math.h>
# include "../../MLX42/include/MLX42/MLX42.h"
#include <stdio.h>
#include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
#include "../../libft/libft.h"

// typedef struct s_player
// {
//     float             px;
//     float             py;
//     float             pdx;
//     float             pdy;
//     float             pa;
//     float             planex;
//     float             planey;
// }               t_player;

// typedef struct s_ray
// {
//     double             rx;
//     double             ry;
//     double             ra;
//     double             hx;
//     double             hy;
//     double             vx;
//     double             vy;

// }               t_ray;

// typedef struct s_map
// {
//     char               **m;
//     double             mx;
//     double             my;
// }               t_map;

// typedef struct s_data
// {
//     mlx_t            *mlx;
//     t_player        *player;
//     t_ray           *ray;
//     t_map           *map;
//     mlx_image_t     *img;
//     int             win_width;
//     int             win_height;
    
// }               t_data;


int 	map_parsing(char **argv);
void	exit_fail(char *message);
int 	map_parsing(char **map);
void 	rgb_range_checker(char *row);
char	**file_parsing(char **argv);

#endif