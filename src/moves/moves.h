/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:31:01 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/06/22 11:22:01 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOVES_H
# define MOVES_H

# include "../cub3d.h"

// key_callback
void	key_callback(mlx_key_data_t data, void *param);
void	update_keys(void *param);
void	mouse_callback(double xpos, double ypos, void *param);
// moves
void	change_direction(mlx_key_data_t data, t_player *player);
void	move_player(t_data *game, mlx_key_data_t data, t_player *player,
			t_map *map);
#endif
