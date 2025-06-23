/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:28:13 by jwardeng          #+#    #+#             */
/*   Updated: 2025/06/23 18:09:26 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "../cub3d.h"

# define WIN_WIDTH 1200
# define WIN_HEIGHT 1080

typedef struct s_player
{
	double			px;
	double			py;
	double			pdx;
	double			pdy;
	double			pa;
	int				xo;
	int				yo;
	double			speed;
}					t_player;

typedef struct s_ray
{
	double			rx;
	double			ry;
	double			ra;
	double			rdx;
	double			rdy;
	int				vert;
	int				mx;
	int				my;
	double			delta_dx;
	double			side_dx;
	double			delta_dy;
	double			side_dy;
	double			walld;
	double			start;
	double			height;
	double			mm_rx;
	double			mm_ry;

}					t_ray;

typedef struct s_map
{
	char			**m;
	double			mx;
	double			my;
}					t_map;

typedef struct s_data
{
	mlx_t			*mlx;
	t_player		*player;
	t_ray			*ray;
	t_map			*map;
	char			**m;
	mlx_image_t		*img;
	mlx_texture_t	*tn;
	mlx_texture_t	*ts;
	mlx_texture_t	*te;
	mlx_texture_t	*tw;
	mlx_texture_t	*d;
	double			tile;
	double			tss;
	int				door;
	uint32_t		sky_color;
	uint32_t		floor;
	int				check_list[6];
}					t_data;

// init
t_data				*init_game(t_data *game);
// init_helper
void				player_pos(t_data *game, char **map, t_player *player,
						int y);
int					tile_size(int x, int y);

#endif