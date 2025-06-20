/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:31:01 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/06/19 10:29:36 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOVES_H
# define MOVES_H

# include "../cub3d.h"

void	key_callback(mlx_key_data_t data, void *param);
void	update_keys(void *param);
void	mouse_callback(double xpos, double ypos, void *param);
#endif
