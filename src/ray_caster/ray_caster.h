/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:45:21 by jwardeng          #+#    #+#             */
/*   Updated: 2025/06/08 16:19:12 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_CASTER_H
# define RAY_CASTER_H

#include <math.h>
# include "../../MLX42/include/MLX42/MLX42.h"
#include <stdio.h>
#include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
#include "../../libft/libft.h"
#include "../cub3d.h"
// # include "../../MLX42/include/MLX42/MLX42_Int.h"


typedef enum s_ray_dir
{
    UP,
    DOWN,
    LEFT,
    RIGHT
}               t_ray_dir;

typedef enum s_tex_type
{
    NORTH,
    SOUTH,
    WEST,
    EAST
}
            t_tex_type;
// typedef struct s_player
// {
//     double             px;
//     double             py;
//     double             pdx;
//     double             pdy;
//     double             pa;
//     double             speed;
// }               t_player;

// typedef struct s_ray
// {
//     double             rx;
//     double             ry;
//     double             ra;
//     double             rdx;
//     double             rdy;

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

// t_data *init_game(char *m);

void cast_rays(t_data *game, t_player *player, t_ray *ray, t_map *map);
void minimap(t_data *game);
int	get_texture_color(mlx_texture_t *texture, int x, int y);
double   get_tx(t_ray *rays, mlx_texture_t *img);
int get_ty(int y_screen, int wall_top, int wall_height, mlx_texture_t *tex);
mlx_texture_t *choose_tex(t_data *game);
#endif