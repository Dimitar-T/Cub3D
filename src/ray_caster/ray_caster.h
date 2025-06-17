/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:45:21 by jwardeng          #+#    #+#             */
/*   Updated: 2025/06/17 17:18:25 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_CASTER_H
# define RAY_CASTER_H

# include "../cub3d.h"

# define FOV 1.0471975512
# define MINIMAP_SCALE 0.15625
// ≈ M_PI / 3
// = 10.0 / 64.0

typedef enum s_ray_dir
{
	UP,
	DOWN,
	LEFT,
	RIGHT
}				t_ray_dir;

typedef enum s_tex_type
{
	NORTH,
	SOUTH,
	WEST,
	EAST
}				t_tex_type;

//ray_caster
void			cast_rays(t_data *game, t_player *player, t_ray *ray,
					t_map *map);
//minimap
void			minimap(t_data *game);
void			mm_cast_rays(t_data *game, t_player *player, t_ray *ray,
					t_map *map);
//textures
int				get_texture_color(mlx_texture_t *texture, int x, int y);
double			get_tx(t_ray *rays, mlx_texture_t *img);
int				get_ty(int y_screen, int wall_top, int wall_height,
					mlx_texture_t *tex);
mlx_texture_t	*choose_tex(t_data *game);
#endif