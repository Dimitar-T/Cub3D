/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:45:21 by jwardeng          #+#    #+#             */
/*   Updated: 2025/06/22 19:21:07 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_CASTER_H
# define RAY_CASTER_H

# include "../cub3d.h"

# define FOV 1.0471975512
// ≈ M_PI / 3

// ray_caster
void	cast_rays(t_data *game, t_player *player, t_ray *ray);
void	calc_walls(int x, t_data *game, t_ray *ray, t_player *player);
void	refresh_image(t_data *game);
// minimap
void	minimap(t_data *game);
void	mm_cast_rays(t_data *game, t_player *player, t_ray *ray, t_map *map);
// textures
int		get_tex_px(t_data *game, int start, int wallheight, int y);
// doors
int		door_d(int map_x, int map_y, t_data *game);
#endif