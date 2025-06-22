/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwardeng <jwardeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:16:43 by jwardeng          #+#    #+#             */
/*   Updated: 2025/06/22 16:28:26 by jwardeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_caster.h"

int	door_d(int map_x, int map_y, t_data *game)
{
	double	distance;

	distance = hypot(game->player->px - (map_x * game->tile + game->tile / 2),
			game->player->py - (map_y * game->tile + game->tile / 2));
	if (distance <= 100)
		return (1);
	else
		return (0);
}
